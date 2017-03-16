#include "log.hpp"
#include "common.h"

using namespace std;

void LogStream::add_stream(std::ostream* stream)
{
  if (stream)
  {
    *stream << fixed;
    _streams.push_back(stream);
  }
}

Logging::Logging() : _log_level(LogLevel::info), _logfile()
{
  /* add file stream to the list, even though it's to attached to a file yet */
  _full_stream.add_stream(&_logfile);
}

Logging& Logging::instance()
{
  static Logging instance;

  return instance;
}

LogStream& Logging::logstream(LogLevel level)
{
  if (ParallelContext::master() && level <= _log_level)
    return _full_stream;
  else
    return _empty_stream;
}

void Logging::set_log_filename(const std::string& fname)
{
  _logfile.open(fname, ofstream::out);
}

void Logging::add_log_stream(std::ostream* stream)
{
  if (stream)
    _full_stream.add_stream(stream);
}

void Logging::set_log_level(LogLevel level)
{
  _log_level = level;
}

Logging& logger()
{
  return Logging::instance();
}

TimeStamp::TimeStamp() : secs(sysutil_elapsed_seconds())
{
};

LogStream& operator<<(LogStream& logstream, std::ostream& (*pf)(std::ostream&))
{
  for (auto s: logstream.streams())
    *s << pf;

  return logstream;
}

LogStream& operator<<(LogStream& logstream, const TimeStamp& ts)
{
  const unsigned int hh = ts.secs / 3600;
  const unsigned int mm = (ts.secs - hh * 3600) / 60;
  const unsigned int ss = (ts.secs - hh * 3600 - mm * 60);

  logstream << setfill('0') << setw(2) << hh << ":" <<
                      setw(2) << mm << ":" <<
                      setw(2) << ss;

  return logstream;
}

LogStream& operator<<(LogStream& logstream, const ProgressInfo& prog)
{

  logstream << "[" << TimeStamp() << " " << FMT_LH(prog.loglh) << "] ";

  return logstream;
}
