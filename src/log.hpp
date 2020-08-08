#ifndef RAXML_LOG_HPP_
#define RAXML_LOG_HPP_

#include <fstream>
#include <vector>
#include <memory>

enum class LogLevel
{
  none = 0,
  error,
  warning,
  info,
  progress,
  verbose,
  debug
};

enum class LogElement
{
  all = 0,
  loglh,
  model,
  brlen
};


struct TimeStamp
{
  TimeStamp();

  double secs;
};

struct ProgressInfo
{
  ProgressInfo(double loglh) : loglh(loglh) {};

  double loglh;
};

typedef std::vector<std::ostream*> StreamList;

class LogStream
{
public:
  LogStream() {};
  LogStream(const StreamList& streams) { _streams = streams; };

  StreamList& streams() { return _streams;};

  void add_stream(std::ostream* stream);

private:
  StreamList _streams;
};

class Logging
{
public:
  static Logging& instance();

  void log_level(LogLevel level);
  LogLevel log_level() const;

  LogStream& logstream(LogLevel level);

  void set_log_filename(const std::string& fname, std::ios_base::openmode mode = std::ios::out);
  void add_log_stream(std::ostream* stream);

  void precision(unsigned int prec, LogElement elem = LogElement::all);
  unsigned int precision(LogElement elem) const;

  /* singleton: remove copy/move constructors and assignment ops */
  Logging(const Logging& other) = delete;
  Logging(Logging&& other) = delete;
  Logging& operator=(const Logging& other) = delete;
  Logging& operator=(Logging&& other) = delete;

private:
  Logging();

  LogLevel _log_level;
  std::ofstream _logfile;
  LogStream _empty_stream;
  LogStream _full_stream;

  unsigned int _precision_loglh;
  unsigned int _precision_model;
  unsigned int _precision_brlen;
};

Logging& logger();

#define RAXML_LOG(level) logger().logstream(level)

#define LOG_ERROR RAXML_LOG(LogLevel::error)
#define LOG_WARN RAXML_LOG(LogLevel::warning)
#define LOG_INFO RAXML_LOG(LogLevel::info)
#define LOG_DEBUG RAXML_LOG(LogLevel::debug)
#define LOG_PROGR RAXML_LOG(LogLevel::progress)
#define LOG_VERB RAXML_LOG(LogLevel::verbose)

#define LOG_INFO_TS LOG_INFO << "[" << TimeStamp() << "] "
#define LOG_VERB_TS LOG_VERB << "[" << TimeStamp() << "] "
#define LOG_DEBUG_TS LOG_DEBUG << "[" << TimeStamp() << "] "
#define LOG_PROGRESS(loglh) LOG_PROGR << ProgressInfo(loglh)

#define FMT_LH(lh) setprecision(logger().precision(LogElement::loglh)) << lh
#define FMT_MOD(p) setprecision(logger().precision(LogElement::model)) << p
#define FMT_BL(bl) setprecision(logger().precision(LogElement::brlen)) << bl
#define FMT_PREC3(val) setprecision(3) << val

template <class T>
LogStream& operator<<(LogStream& logstream, const T& object)
{
  for (auto s: logstream.streams())
    *s << object;

  return logstream;
}

LogStream& operator<<(LogStream& logstream, std::ostream& (*pf)(std::ostream&));
LogStream& operator<<(LogStream& logstream, const ProgressInfo& prog);
LogStream& operator<<(LogStream& logstream, const TimeStamp& ts);
LogStream& operator<<(LogStream& logstream, const time_t& t);


#endif /* RAXML_LOG_HPP_ */
