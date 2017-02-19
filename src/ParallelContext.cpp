#include "ParallelContext.hpp"

#include "Options.hpp"

using namespace std;

size_t ParallelContext::_num_threads;
std::vector<std::thread> ParallelContext::_threads;
std::vector<double> ParallelContext::_parallel_buf;
std::unordered_map<std::thread::id, ParallelContext> ParallelContext::_thread_ctx_map;

void ParallelContext::init(const Options& opts, std::function<void()> thread_main)
{
  _num_threads = opts.num_threads;
  _parallel_buf.reserve(opts.num_threads * 16);

  _thread_ctx_map.emplace(std::this_thread::get_id(), ParallelContext(0));

  /* Launch threads */
  for (size_t i = 1; i < _num_threads; ++i)
  {
    _threads.emplace_back(thread_main);
    _thread_ctx_map.emplace(_threads.back().get_id(), ParallelContext(i));
  }
}

void ParallelContext::finalize()
{
  for (thread& t: _threads)
    t.join();
  _threads.clear();
}

void ParallelContext::parallel_thread_barrier() const
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

void ParallelContext::parallel_thread_reduce(double * data, size_t size) const
{
  /* synchronize */
  parallel_thread_barrier();

  /* collect data from threads */
  size_t i, j;
  for (i = 0; i < size; ++i)
    _parallel_buf[_thread_id * size + i] = data[i];

  /* synchronize */
  parallel_thread_barrier();

  /* reduce */
  for (i = 0; i < size; ++i)
  {
    data[i] = 0.;
    for (j = 0; j < ParallelContext::_num_threads; ++j)
      data[i] += _parallel_buf[j * size + i];
  }

  //needed?
//  parallel_barrier(useropt);
}


void ParallelContext::parallel_reduce(double * data, size_t size) const
{
//  printf("P%u T%u: %lf\n", useropt->process_id, useropt->thread_id, data[0]);

#ifdef _USE_PTHREADS
  parallel_thread_reduce(data, size);
#endif

#ifdef _USE_MPI
  MPI_Allreduce(MPI_IN_PLACE, data, size, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
#endif
}

void ParallelContext::parallel_reduce_cb(void * context, double * data, size_t size)
{
  (static_cast<const ParallelContext *>(context))->parallel_reduce(data, size);
}

void ParallelContext::thread_broadcast(size_t source_id, void * data, size_t size) const
{
  /* write to buf */
  if (_thread_id == source_id)
  {
    memcpy((void *) _parallel_buf.data(), data, size);
  }

  /* synchronize */
  barrier();

//  pthread_barrier_wait(&barrier);
  __sync_synchronize();

  /* read from buf*/
  if (_thread_id != source_id)
  {
    memcpy(data, (void *) _parallel_buf.data(), size);
  }

  barrier();
}
