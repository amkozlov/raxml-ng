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

LogStream& Logging::logstream(LogLevel level, bool worker)
{
  if ((ParallelContext::master() || (ParallelContext::group_master() && worker))
      && level <= _log_level)
    return _full_stream;
  else
    return _empty_stream;
}

void Logging::set_log_filename(const std::string& fname, ios_base::openmode mode)
{
  _logfile.open(fname, mode);
  if (_logfile.fail())
  {
    throw runtime_error("Cannot open the log file for writing: " + fname +
        "\nPlease make sure directory exists and you have write permissions for it!");
  }
}

void Logging::add_log_stream(std::ostream* stream)
{
  if (stream)
    _full_stream.add_stream(stream);
}

void Logging::log_level(LogLevel level)
{
  _log_level = level;
}

LogLevel Logging::log_level() const
{
  return _log_level;
}

void Logging::precision(const LogElementMap& prec)
{
  _precision = prec;
}

void Logging::precision(unsigned int prec, LogElement elem)
{
  _precision[elem] = prec;
}

unsigned int Logging::precision(LogElement elem) const
{
  if (_precision.count(elem))
    return _precision.at(elem);
  else if (_precision.count(LogElement::all))
    return _precision.at(LogElement::all);
  else
    return RAXML_DEFAULT_PRECISION;
}

Logging& logger()
{
  return Logging::instance();
}


TimeStamp::TimeStamp() : secs(global_timer().elapsed_seconds())
{
};

LogStream& operator<<(LogStream& logstream, std::ostream& (*pf)(std::ostream&))
{
  for (auto s: logstream.streams())
    *s << pf;

  return logstream;
}

LogStream& operator<<(LogStream& logstream, const time_t& t)
{
  logstream << sysutil_fmt_time(t);

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
