#include "SystemTimer.hpp"

using namespace std;

double SystemTimer::elapsed_seconds() const
{
  chrono::time_point<chrono::system_clock> end_time = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_time - _start_time;
  return elapsed_seconds.count();
}

time_t SystemTimer::start_time() const
{
  return std::chrono::system_clock::to_time_t(_start_time);
}

time_t SystemTimer::current_time() const
{
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  return std::chrono::system_clock::to_time_t(now);
}
