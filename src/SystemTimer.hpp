#ifndef RAXML_SYSTEMTIMER_HPP_
#define RAXML_SYSTEMTIMER_HPP_

#include <chrono>

class SystemTimer
{
public:
  SystemTimer () : _start_time(std::chrono::system_clock::now()) {}

  time_t start_time() const;
  time_t current_time() const;
  double elapsed_seconds() const;
private:
  std::chrono::time_point<std::chrono::system_clock> _start_time;
};

#endif /* RAXML_SYSTEMTIMER_HPP_ */
