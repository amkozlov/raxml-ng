#ifndef RAXML_PARALLELCONTEXT_HPP_
#define RAXML_PARALLELCONTEXT_HPP_

#include <thread>
#include <vector>
#include <unordered_map>
#include <memory>

class Options;

class ParallelContext
{
public:
  static void init(const Options& opts, const std::function<void()>& thread_main);

  static void finalize();

  static const ParallelContext& ctx() { return ParallelContext::_thread_ctx_map.at(std::this_thread::get_id()); }
  static size_t num_procs() { return _num_threads; };

  static void parallel_reduce_cb(void * context, double * data, size_t size, int op);
  void parallel_thread_reduce(double * data, size_t size, int op) const;
  void thread_broadcast(size_t source_id, void * data, size_t size) const;
  void thread_send_master(size_t source_id, void * data, size_t size) const;

  static bool is_master() { return _thread_ctx_map.empty() || ctx().master(); }

  template<class T>
  static std::unique_ptr<T> master_broadcast(T const& object)
  {
    T const* p_object = &object;

#ifdef _USE_PTHREADS
    ParallelContext::ctx().thread_broadcast(0, &p_object, sizeof(T *));
#endif

    std::unique_ptr<T> result(new T(*p_object));

#ifdef _USE_PTHREADS
    ParallelContext::ctx().barrier();
#endif

    return result;
  }

  size_t thread_id() const { return _thread_id; }
  bool master() const { return _thread_id == 0; }
  void barrier() const { parallel_thread_barrier(); };
//  static void barrier() { ctx().barrier(); };

private:
  static std::vector<std::thread> _threads;
  static size_t _num_threads;
  static std::vector<double> _parallel_buf;
  static std::unordered_map<std::thread::id, ParallelContext> _thread_ctx_map;

  size_t _thread_id;

  ParallelContext (size_t thread_id) : _thread_id(thread_id) {};

  void parallel_thread_barrier() const;
  void parallel_reduce(double * data, size_t size, int op) const;
};

#endif /* RAXML_PARALLELCONTEXT_HPP_ */
