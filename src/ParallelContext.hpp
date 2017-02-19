#ifndef RAXML_PARALLELCONTEXT_HPP_
#define RAXML_PARALLELCONTEXT_HPP_

#include <thread>
#include <vector>
#include <unordered_map>

class Options;

class ParallelContext
{
public:
//  template< class Function, class... Args >
//  static void init(const Options& opts, Function&& thread_main, Args&&... thread_args)
//  {
//    _num_threads = opts.num_threads;
//    _parallel_buf.reserve(opts.num_threads * 16);
//
//    _thread_ctx_map.emplace(std::this_thread::get_id(), ParallelContext(0));
//
//    /* Launch threads */
//    for (size_t i = 1; i < _num_threads; ++i)
//    {
//      _threads.emplace_back(thread_main, thread_args...);
//      _thread_ctx_map.emplace(_threads.back().get_id(), ParallelContext(i));
//    }
//  }

  static void init(const Options& opts, std::function<void()> thread_main);

  static void finalize();

  static const ParallelContext& ctx() { return ParallelContext::_thread_ctx_map.at(std::this_thread::get_id()); }
  static size_t num_procs() { return _num_threads; };

  static void parallel_reduce_cb(void * context, double * data, size_t size);
  void parallel_thread_reduce(double * data, size_t size) const;
  void thread_broadcast(size_t source_id, void * data, size_t size) const;

  static bool is_master() { return _thread_ctx_map.empty() || ctx().master(); }

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
  void parallel_reduce(double * data, size_t size) const;
};

#endif /* RAXML_PARALLELCONTEXT_HPP_ */
