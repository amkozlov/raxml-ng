#ifndef RAXML_PARALLELCONTEXT_HPP_
#define RAXML_PARALLELCONTEXT_HPP_

#include <vector>
#include <unordered_map>
#include <memory>

#include <functional>

#ifdef _RAXML_MPI
#include <mpi.h>
#endif

#ifdef _RAXML_PTHREADS
#include <thread>
#include <mutex>
typedef std::thread ThreadType;
typedef std::thread::id ThreadIDType;
typedef std::mutex MutexType;
typedef std::unique_lock<std::mutex> LockType;
#else
typedef int ThreadType;
typedef size_t ThreadIDType;
typedef int MutexType;
typedef int LockType;
#endif

class Options;

struct ThreadGroup
{
  size_t group_id;
  size_t num_threads;
  MutexType mtx;
  std::vector<char> reduction_buf;

  volatile unsigned int barrier_counter;
  volatile int proceed;

  ThreadGroup(size_t id, size_t size) :
    group_id(id), num_threads(size), mtx(), barrier_counter(0), proceed(0) {}

  ThreadGroup(ThreadGroup&& other):
    group_id(other.group_id), num_threads(other.num_threads), mtx(),
    reduction_buf(std::move(other.reduction_buf)),
    barrier_counter(other.barrier_counter), proceed(other.proceed) {}
};

class ParallelContext
{
public:
  static void init_mpi(int argc, char * argv[], void * comm);
  static void init_pthreads(const Options& opts, const std::function<void()>& thread_main);
  static void resize_buffer(size_t size);

  static void finalize(bool force = false);

  static size_t num_procs() { return _num_ranks * _num_threads; }
  static size_t num_threads() { return _num_threads; }
  static size_t num_ranks() { return _num_ranks; }
  static size_t num_nodes() { return _num_nodes; }
  static size_t num_groups() { return _num_groups; }
  static size_t ranks_per_node() { return _num_ranks / _num_nodes; }
  static size_t threads_per_group() { return num_procs() / _num_groups; }
  static size_t ranks_per_group() { return _num_ranks / _num_groups; }

  static void parallel_reduce_cb(void * context, double * data, size_t size, int op);
  static void thread_reduce(double * data, size_t size, int op);
  static void thread_broadcast(size_t source_id, void * data, size_t size);
  void thread_send_master(size_t source_id, void * data, size_t size) const;

  static void mpi_broadcast(void * data, size_t size);
  static void mpi_gather_custom(std::function<int(void*,int)> prepare_send_cb,
                                std::function<void(void*,int)> process_recv_cb);

  static bool master() { return proc_id() == 0; }
  static bool master_rank() { return _rank_id == 0; }
  static bool master_thread() { return _thread_id == 0; }
  static size_t thread_id() { return _thread_id; }
  static size_t rank_id() { return _rank_id; }
  static size_t proc_id() { return _rank_id * _num_threads + _thread_id; }

  static size_t local_thread_id() { return _local_thread_id; }
  static size_t local_rank_id() { return _local_rank_id; }
  static size_t local_proc_id() { return _local_rank_id * _num_threads + _local_thread_id; }
  static size_t group_id() { return _thread_group->group_id; }

  static bool group_master() { return local_proc_id() == 0; }
  static bool group_master_rank() { return _local_rank_id == 0; }
  static bool group_master_thread() { return _local_thread_id == 0; }

  static void barrier();
  static void global_barrier();
  static void thread_barrier();
  static void global_thread_barrier();
  static void mpi_barrier();
  static void global_mpi_barrier();

  /* static singleton, no instantiation/copying/moving */
  ParallelContext() = delete;
  ParallelContext(const ParallelContext& other) = delete;
  ParallelContext(ParallelContext&& other) = delete;
  ParallelContext& operator=(const ParallelContext& other) = delete;
  ParallelContext& operator=(ParallelContext&& other) = delete;

  class UniqueLock
  {
  public:
    UniqueLock() : _lock(mtx) {}
  private:
    LockType _lock;
  };

  class GroupLock
  {
  public:
    GroupLock() : _lock(_thread_group->mtx) {}
  private:
    LockType _lock;
  };

private:
  static std::vector<ThreadType> _threads;
  static size_t _num_threads;
  static size_t _num_ranks;
  static size_t _num_nodes;
  static size_t _num_groups;
  static std::vector<char> _parallel_buf;
  static std::unordered_map<ThreadIDType, ParallelContext> _thread_ctx_map;
  static MutexType mtx;

  static size_t _rank_id;
  static size_t _local_rank_id;
  static thread_local size_t _thread_id;
  static thread_local size_t _local_thread_id;
  static thread_local ThreadGroup * _thread_group;

  static std::vector<ThreadGroup> _thread_groups;

#ifdef _RAXML_MPI
  static bool _owns_comm;
  static MPI_Comm _comm;
#endif

  static void start_thread(size_t thread_id, size_t local_thread_id,
                           ThreadGroup& thread_grp,
                           const std::function<void()>& thread_main);
  static void parallel_reduce(double * data, size_t size, int op);
  static void detect_num_nodes();
};

#endif /* RAXML_PARALLELCONTEXT_HPP_ */
