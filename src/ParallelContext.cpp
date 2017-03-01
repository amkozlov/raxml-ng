#include "ParallelContext.hpp"

#include "Options.hpp"

using namespace std;

size_t ParallelContext::_num_threads = 1;
size_t ParallelContext::_num_ranks = 1;
size_t ParallelContext::_rank_id = 0;
std::vector<ThreadType> ParallelContext::_threads;
std::vector<double> ParallelContext::_parallel_buf;
std::unordered_map<ThreadIDType, ParallelContext> ParallelContext::_thread_ctx_map;
MutexType ParallelContext::mtx;

void ParallelContext::init_mpi(int argc, char * argv[])
{
#ifdef _RAXML_MPI
  {
    int tmp;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &tmp);
    _rank_id = (size_t) tmp;
    MPI_Comm_size(MPI_COMM_WORLD, &tmp);
    _num_ranks = (size_t) tmp;
//    printf("size: %lu, rank: %lu\n", _num_ranks, _rank_id);
  }
#endif

  /* add master thread to the map */
#ifdef _RAXML_PTHREADS
  _thread_ctx_map.emplace(std::this_thread::get_id(), ParallelContext(0));
#else
  _thread_ctx_map.emplace(0, ParallelContext(0));
#endif
}

void ParallelContext::init_pthreads(const Options& opts, const std::function<void()>& thread_main)
{
  _num_threads = opts.num_threads;
  _parallel_buf.reserve(opts.num_threads * 4096);

#ifdef _RAXML_PTHREADS
  _thread_ctx_map.emplace(std::this_thread::get_id(), ParallelContext(0));

  /* Launch threads */
  for (size_t i = 1; i < _num_threads; ++i)
  {
    _threads.emplace_back(thread_main);
    _thread_ctx_map.emplace(_threads.back().get_id(), ParallelContext(i));
  }
#endif
}

void ParallelContext::finalize()
{
  for (thread& t: _threads)
    t.join();
  _threads.clear();

#ifdef _RAXML_MPI
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
#endif
}

const ParallelContext& ParallelContext::ctx()
{
  ThreadIDType id;

#ifdef _RAXML_PTHREADS
  id = std::this_thread::get_id();
#else
  id = 0;
#endif

  return ParallelContext::_thread_ctx_map.at(id);
}

void ParallelContext::barrier() const
{
#ifdef _RAXML_MPI
  mpi_barrier();
#endif

#ifdef _RAXML_PTHREADS
  thread_barrier();
#endif
}

void ParallelContext::mpi_barrier() const
{
#ifdef _RAXML_MPI
  if (_thread_id == 0 && _num_ranks > 1)
    MPI_Barrier(MPI_COMM_WORLD);
#endif
}

void ParallelContext::thread_barrier() const
{
  static volatile unsigned int barrier_counter = 0;
  static __thread volatile int myCycle = 0;
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

void ParallelContext::thread_reduce(double * data, size_t size, int op) const
{
  /* synchronize */
  thread_barrier();

  /* collect data from threads */
  size_t i, j;
  for (i = 0; i < size; ++i)
    _parallel_buf[_thread_id * size + i] = data[i];

  /* synchronize */
  thread_barrier();

  /* reduce */
  for (i = 0; i < size; ++i)
  {
    switch(op)
    {
      case PLLMOD_TREE_REDUCE_SUM:
      {
        data[i] = 0.;
        for (j = 0; j < ParallelContext::_num_threads; ++j)
          data[i] += _parallel_buf[j * size + i];
      }
      break;
      case PLLMOD_TREE_REDUCE_MAX:
      {
        data[i] = _parallel_buf[i];
        for (j = 1; j < ParallelContext::_num_threads; ++j)
          data[i] = max(data[i], _parallel_buf[j * size + i]);
      }
      break;
      case PLLMOD_TREE_REDUCE_MIN:
      {
        data[i] = _parallel_buf[i];
        for (j = 1; j < ParallelContext::_num_threads; ++j)
          data[i] = min(data[i], _parallel_buf[j * size + i]);
      }
      break;
    }
  }

  //needed?
//  parallel_barrier(useropt);
}


void ParallelContext::parallel_reduce(double * data, size_t size, int op) const
{
#ifdef _RAXML_PTHREADS
  if (_num_threads > 1)
    thread_reduce(data, size, op);
#endif

#ifdef _RAXML_MPI
  if (_num_ranks > 1)
  {
    thread_barrier();

    if (_thread_id == 0)
    {
      MPI_Op reduce_op;
      if (op == PLLMOD_TREE_REDUCE_SUM)
        reduce_op = MPI_SUM;
      else if (op == PLLMOD_TREE_REDUCE_MAX)
        reduce_op = MPI_MAX;
      else if (op == PLLMOD_TREE_REDUCE_MIN)
        reduce_op = MPI_MIN;
      else
        assert(0);

      MPI_Allreduce(MPI_IN_PLACE, data, size, MPI_DOUBLE, reduce_op, MPI_COMM_WORLD);
    }

    if (_num_threads > 1)
      thread_broadcast(0, data, size * sizeof(double));
  }
#endif
}

void ParallelContext::parallel_reduce_cb(void * context, double * data, size_t size, int op)
{
  (static_cast<const ParallelContext *>(context))->parallel_reduce(data, size, op);
}

void ParallelContext::thread_broadcast(size_t source_id, void * data, size_t size) const
{
  /* write to buf */
  if (_thread_id == source_id)
  {
    memcpy((void *) _parallel_buf.data(), data, size);
  }

  /* synchronize */
  thread_barrier();

//  pthread_barrier_wait(&barrier);
  __sync_synchronize();

  /* read from buf*/
  if (_thread_id != source_id)
  {
    memcpy(data, (void *) _parallel_buf.data(), size);
  }

  thread_barrier();
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

