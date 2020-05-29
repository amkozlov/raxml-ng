#include "ParallelContext.hpp"

#include "Options.hpp"

#include "util/EnergyMonitor.hpp"

using namespace std;

// This is just a default size; the buffer will be resized later according to #part and #threads
#define PARALLEL_BUF_SIZE (128 * 1024)

size_t ParallelContext::_num_threads = 1;
size_t ParallelContext::_num_ranks = 1;
size_t ParallelContext::_num_nodes = 1;
size_t ParallelContext::_num_groups = 1;
size_t ParallelContext::_rank_id = 0;
size_t ParallelContext::_local_rank_id = 0;
bool ParallelContext::_node_master_rank = true;
std::string ParallelContext::_node_name = "";
thread_local size_t ParallelContext::_thread_id = 0;
std::vector<ThreadType> ParallelContext::_threads;
std::vector<char> ParallelContext::_parallel_buf;
std::unordered_map<ThreadIDType, ParallelContext> ParallelContext::_thread_ctx_map;
MutexType ParallelContext::mtx;

thread_local size_t ParallelContext::_local_thread_id = 0;
thread_local ThreadGroup * ParallelContext::_thread_group = nullptr;
std::vector<ThreadGroup> ParallelContext::_thread_groups;


#ifdef _RAXML_MPI
MPI_Comm ParallelContext::_comm = MPI_COMM_WORLD;
bool ParallelContext::_owns_comm = true;
#endif

ThreadGroup& ParallelContext::thread_group(size_t id)
{
  if (id < _thread_groups.size())
    return _thread_groups[id];
  else
    throw runtime_error("Invalid thread group id: " + to_string(id));
}

void ParallelContext::init_mpi(int argc, char * argv[], void * comm)
{
#ifdef _RAXML_MPI
  {
    int tmp;

    _parallel_buf.reserve(PARALLEL_BUF_SIZE);

    if (comm)
    {
      // TODO we should think how to get rid of this ugly cast!
      _comm = *((MPI_Comm*) comm);
      _owns_comm = false;
    }
    else
    {
      _comm = MPI_COMM_WORLD;
      _owns_comm = true;
      MPI_Init(&argc, &argv);
    }

    MPI_Comm_rank(_comm, &tmp);
    _rank_id = (size_t) tmp;
    MPI_Comm_size(_comm, &tmp);
    _num_ranks = (size_t) tmp;
//    printf("size: %lu, rank: %lu\n", _num_ranks, _rank_id);

    detect_num_nodes();
//    printf("nodes: %lu\n", _num_nodes);
  }
#else
  RAXML_UNUSED(argc);
  RAXML_UNUSED(argv);
  RAXML_UNUSED(comm);
#endif
}

void ParallelContext::start_thread(size_t thread_id, size_t local_thread_id,
                                   ThreadGroup& thread_grp,
                                   const std::function<void()>& thread_main)
{
  ParallelContext::_thread_id = thread_id;
  ParallelContext::_local_thread_id = local_thread_id;
  ParallelContext::_thread_group = &thread_grp;
  thread_main();
}

#ifdef _RAXML_PTHREADS
static void pin_thread(size_t core_id, pthread_t thread)
{
#ifdef __linux__
  // Create a cpu_set_t object representing a set of CPUs. Clear it and mark
  // only CPU i as set.
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core_id, &cpuset);
  int rc = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  if (rc != 0)
    std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
#else
  RAXML_UNUSED(core_id);
  RAXML_UNUSED(thread);
  LOG_WARN << "WARNING: Thread pinning is not supported on non-Linux systems!" << std::endl;
#endif
}
#endif

void ParallelContext::init_pthreads(const Options& opts, const std::function<void()>& thread_main)
{
  _num_threads = opts.num_threads;
  _num_groups = std::max(opts.num_workers, 1u);
  _parallel_buf.reserve(PARALLEL_BUF_SIZE);

  _local_rank_id = _num_ranks > _num_groups ? _rank_id : 0;

  /* init thread groups */
  size_t groups_per_rank = _num_groups > 1 ? _num_groups / _num_ranks : 1;
  size_t group_size = opts.num_threads / std::max(groups_per_rank, 1lu);
  auto start_grp_id = _num_groups > 1 ? _rank_id * groups_per_rank : 0;
  for (size_t i = 0; i < groups_per_rank; ++i)
    _thread_groups.emplace_back(start_grp_id + i, i, group_size, PARALLEL_BUF_SIZE);

  assert(!_thread_groups.empty());

#ifdef _RAXML_PTHREADS
  /* Launch/init threads */
  auto grp = _thread_groups.begin();
  for (size_t i = 0, local_id = 0; i < _num_threads; ++i, ++local_id)
  {
    if (local_id >= grp->num_threads)
    {
      local_id = 0;
      grp++;
    }

    if (i == 0)
    {
      /* init master thread */
      _local_thread_id = local_id;
      _thread_group = &(*grp);
    }
    else
      _threads.emplace_back(ParallelContext::start_thread, i, local_id, std::ref(*grp), thread_main);

    if (opts.thread_pinning && _num_threads > 1)
    {
      auto handle = i > 0 ? _threads.back().native_handle() : pthread_self();
      pin_thread(i, handle);
    }
  }
#endif
}

void ParallelContext::detect_num_nodes()
{
#ifdef _RAXML_MPI
  if (_num_ranks > 1)
  {
    int len;
    char name[MPI_MAX_PROCESSOR_NAME];
    unordered_set<string> node_names;
    NameIdMap node_minrank;
    vector<char> node_master(_num_ranks, 0);

    MPI_Get_processor_name(name, &len);

//    printf("\n hostname: %s,  len; %d\n", name, len);

    _node_name = name;

    if (master())
    {
      node_names.insert(_node_name);
      node_minrank[_node_name] = _rank_id;
    }

    /* send callback -> work rank: send host name to master */
    auto worker_cb = [name,len](void * buf, size_t buf_size) -> size_t
        {
          assert((size_t) len < buf_size);
          memcpy(buf, name, (len+1) * sizeof(char));
          return len;
        };

    /* receive callback -> master rank: collect host names */
    auto master_cb = [&node_names,&node_minrank](void * buf, size_t buf_size, size_t rank)
       {
        char * name = (char*) buf;
        node_names.insert(name);
        if (!node_minrank.count(name) || node_minrank[name] > rank)
          node_minrank[name] = rank;
        RAXML_UNUSED(buf_size);
       };

    ParallelContext::mpi_gather_custom(worker_cb, master_cb);

    if (master())
    {
      /* number of nodes = number of unique hostnames */
      _num_nodes = node_names.size();

      /* determine node master ranks -> first rank on each node */
      for (const auto& pair: node_minrank)
        node_master[pair.second] = 1;
    }

    /* broadcast number of nodes from master */
    MPI_Bcast(&_num_nodes, sizeof(size_t), MPI_BYTE, 0, _comm);

    /* scatter "node master" flags from master to all ranks */
    char tmp;
    MPI_Scatter(node_master.data(), 1, MPI_BYTE, &tmp, 1, MPI_BYTE, 0, _comm);
    _node_master_rank = (tmp == 1);
//    printf("RANK %lu, NODE_MASTER: %s\n", _rank_id, _node_master_rank ? "YES" : "NO");
  }
  else
    _num_nodes = 1;
#else
  _num_nodes = 1;
#endif
}

void ParallelContext::resize_buffers(size_t reduce_buf_size, size_t worker_buf_size)
{
  _parallel_buf.reserve(worker_buf_size);
  for (auto& grp: _thread_groups)
    grp.reduction_buf.reserve(reduce_buf_size);
}

void ParallelContext::finalize(bool force)
{
#ifdef _RAXML_PTHREADS
  for (thread& t: _threads)
  {
    if (force)
      t.detach();
    else
      t.join();
  }
  _threads.clear();
#endif

#ifdef _RAXML_MPI
  if (_owns_comm)
  {
    if (force)
      MPI_Abort(_comm, -1);
    else
      MPI_Barrier(_comm);

    MPI_Finalize();
  }
  else
    MPI_Barrier(_comm);
#endif
}

void ParallelContext::barrier()
{
#ifdef _RAXML_MPI
  mpi_barrier();
#endif

#ifdef _RAXML_PTHREADS
  thread_barrier();
#endif
}

void ParallelContext::global_barrier()
{
#ifdef _RAXML_MPI
  global_mpi_barrier();
#endif

#ifdef _RAXML_PTHREADS
  global_thread_barrier();
#endif
}

void ParallelContext::global_mpi_barrier()
{
#ifdef _RAXML_MPI
  if (_thread_id == 0 && _num_ranks > 1)
    MPI_Barrier(_comm);
#endif
}

void ParallelContext::mpi_barrier()
{
#ifdef _RAXML_MPI
  // TODO: support multiple ranks per worker
  if (_thread_id == 0 && _num_ranks > _num_groups)
    MPI_Barrier(_comm);
#endif
}


void ParallelContext::global_thread_barrier()
{
  static volatile unsigned int barrier_counter = 0;
  static thread_local volatile int myCycle = 0;
  static volatile int proceed = 0;

  __sync_fetch_and_add( &barrier_counter, 1);

  if(_thread_id == 0)
  {
    while(barrier_counter != ParallelContext::_num_threads);
    barrier_counter = 0;
    proceed = !proceed;
  }
  else
  {
    while(myCycle == proceed);
    myCycle = !myCycle;
  }
}

void ParallelContext::thread_barrier()
{
  static thread_local volatile int myCycle = 0;
  auto& g = *_thread_group;

  if (g.num_threads == 1)
    return;

  __sync_fetch_and_add(&g.barrier_counter, 1);

  if(_local_thread_id == 0)
  {
    while(g.barrier_counter != g.num_threads);
    g.barrier_counter = 0;
    g.proceed = !g.proceed;
  }
  else
  {
    while(myCycle == g.proceed);
    myCycle = !myCycle;
  }
}


void ParallelContext::thread_reduce(double * data, size_t size, int op)
{
  /* synchronize */
  thread_barrier();

  double *double_buf = (double*) _thread_group->reduction_buf.data();
  size_t num_group_threads =  _thread_group->num_threads;

  /* collect data from threads */
  size_t i, j;
  for (i = 0; i < size; ++i)
    double_buf[_local_thread_id * size + i] = data[i];

  /* synchronize */
  thread_barrier();

  /* reduce */
  for (i = 0; i < size; ++i)
  {
    switch(op)
    {
      case PLLMOD_COMMON_REDUCE_SUM:
      {
        data[i] = 0.;
        for (j = 0; j < num_group_threads; ++j)
          data[i] += double_buf[j * size + i];
      }
      break;
      case PLLMOD_COMMON_REDUCE_MAX:
      {
        data[i] = double_buf[i];
        for (j = 1; j < num_group_threads; ++j)
          data[i] = max(data[i], double_buf[j * size + i]);
      }
      break;
      case PLLMOD_COMMON_REDUCE_MIN:
      {
        data[i] = double_buf[i];
        for (j = 1; j < num_group_threads; ++j)
          data[i] = min(data[i], double_buf[j * size + i]);
      }
      break;
    }
  }
}

void ParallelContext::mpi_reduce(double * data, size_t size, int op)
{
#ifdef _RAXML_MPI
  if (_num_ranks > 1)
  {
      MPI_Op reduce_op;
      if (op == PLLMOD_COMMON_REDUCE_SUM)
        reduce_op = MPI_SUM;
      else if (op == PLLMOD_COMMON_REDUCE_MAX)
        reduce_op = MPI_MAX;
      else if (op == PLLMOD_COMMON_REDUCE_MIN)
        reduce_op = MPI_MIN;
      else
        assert(0);

      MPI_Reduce(data, _parallel_buf.data(), size, MPI_DOUBLE, reduce_op, 0, _comm);
      memcpy(data, _parallel_buf.data(), size * sizeof(double));
  }
#else
  RAXML_UNUSED(data);
  RAXML_UNUSED(size);
  RAXML_UNUSED(op);
#endif
}

void ParallelContext::parallel_reduce_cb(void * context, double * data, size_t size, int op)
{
  RAXML_UNUSED(context);
  if (ParallelContext::threads_per_group() > 1)
    ParallelContext::parallel_reduce(data, size, op);
  if (node_master())
    global_energy_monitor.update(10.);
}

void ParallelContext::parallel_reduce(double * data, size_t size, int op)
{
#ifdef _RAXML_PTHREADS
  if (_thread_group->num_threads > 1)
    thread_reduce(data, size, op);
#endif

#ifdef _RAXML_MPI
  mpi_allreduce(data, size, op);
#endif
}

void ParallelContext::mpi_allreduce(double * data, size_t size, int op)
{
#ifdef _RAXML_MPI
  if (_num_ranks > _num_groups)
  {
    thread_barrier();

    if (_thread_id == 0)
    {
      MPI_Op reduce_op;
      if (op == PLLMOD_COMMON_REDUCE_SUM)
        reduce_op = MPI_SUM;
      else if (op == PLLMOD_COMMON_REDUCE_MAX)
        reduce_op = MPI_MAX;
      else if (op == PLLMOD_COMMON_REDUCE_MIN)
        reduce_op = MPI_MIN;
      else
        assert(0);

#if 1
      MPI_Allreduce(MPI_IN_PLACE, data, size, MPI_DOUBLE, reduce_op, _comm);
#else
      // not sure if MPI_IN_PLACE will work in all cases...
      MPI_Allreduce(data, _parallel_buf.data(), size, MPI_DOUBLE, reduce_op, _comm);
      memcpy(data, _parallel_buf.data(), size * sizeof(double));
#endif
    }

    if (_thread_group->num_threads > 1)
      thread_broadcast(0, data, size * sizeof(double));
  }
#else
  RAXML_UNUSED(data);
  RAXML_UNUSED(size);
  RAXML_UNUSED(op);
#endif
}

void ParallelContext::thread_broadcast(size_t source_id, void * data, size_t size)
{
  /* write to buf */
  if (_thread_id == source_id)
  {
    memcpy((void *) _parallel_buf.data(), data, size);
  }

  /* synchronize */
  global_thread_barrier();

//  pthread_barrier_wait(&barrier);
  __sync_synchronize();

  /* read from buf*/
  if (_thread_id != source_id)
  {
    memcpy(data, (void *) _parallel_buf.data(), size);
  }

  global_thread_barrier();
}

void ParallelContext::mpi_broadcast(void * data, size_t size)
{
#ifdef _RAXML_MPI
  if (_num_ranks > 1)
    MPI_Bcast(data, size, MPI_BYTE, 0, _comm);
#else
  RAXML_UNUSED(data);
  RAXML_UNUSED(size);
#endif
}

void ParallelContext::global_master_broadcast(void * data, size_t size)
{
  if (master_thread())
    mpi_broadcast(data, size);
  global_thread_barrier();
  thread_broadcast(0, data, size);
}

void ParallelContext::thread_send_master(size_t source_id, void * data, size_t size) const
{
  /* write to buf */
  if (_thread_id == source_id && data && size)
  {
    memcpy((void *) _parallel_buf.data(), data, size);
  }

  /* synchronize */
  barrier();

//  pthread_barrier_wait(&barrier);
  __sync_synchronize();

  /* read from buf*/
  if (_thread_id == 0)
  {
    memcpy(data, (void *) _parallel_buf.data(), size);
  }

  barrier();
}

void ParallelContext::mpi_gather_custom(std::function<size_t(void*,size_t)> prepare_send_cb,
                                        std::function<void(void*,size_t, size_t)> process_recv_cb)
{
#ifdef _RAXML_MPI
  /* we're gonna use _parallel_buf, so make sure other threads don't interfere... */
  UniqueLock lock;

  if (_rank_id == 0)
  {
    for (size_t r = 1; r < _num_ranks; ++r)
    {
      int recv_size;
      MPI_Status status;
      MPI_Probe(r, 0, _comm, &status);
      MPI_Get_count(&status, MPI_BYTE, &recv_size);

//      printf("recv: %lu\n", recv_size);

      _parallel_buf.reserve(recv_size);

      MPI_Recv((void*) _parallel_buf.data(), recv_size, MPI_BYTE,
               r, 0, _comm, MPI_STATUS_IGNORE);

      process_recv_cb(_parallel_buf.data(), (size_t) recv_size, r);
    }
  }
  else
  {
    auto send_size = prepare_send_cb(_parallel_buf.data(), _parallel_buf.capacity());
//    printf("sent: %lu\n", send_size);

    MPI_Send(_parallel_buf.data(), send_size, MPI_BYTE, 0, 0, _comm);
  }
#else
  RAXML_UNUSED(prepare_send_cb);
  RAXML_UNUSED(process_recv_cb);
#endif
}

