#ifndef RAXML_LOG_HPP_
#define RAXML_LOG_HPP_

class ParallelContext;

class Logger
{
public:
  static std::ostream& info() { return std::cout; }
};

//#define LOG_INFO if (!ParallelContext::is_master()) {} else Logger::info()
#define LOG_INFO std::cout

void print_progress(double loglh, const char* format, ... );

#endif /* RAXML_LOG_HPP_ */
