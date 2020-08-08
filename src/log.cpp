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

Logging::Logging() : _log_level(LogLevel::info), _logfile(),
    _precision_loglh(RAXML_DEFAULT_PRECISION), _precision_model(RAXML_DEFAULT_PRECISION),
    _precision_brlen(RAXML_DEFAULT_PRECISION)
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

void Logging::set_log_filename(const std::string& fname, ios_base::openmode mode)
{
  _logfile.open(fname, mode);
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

void Logging::precision(unsigned int prec, LogElement elem)
{
  switch(elem)
  {
    case LogElement::loglh:
      _precision_loglh = prec;
      break;
    case LogElement::model:
      _precision_model = prec;
      break;
    case LogElement::brlen:
      _precision_brlen = prec;
      break;
    case LogElement::all:
      _precision_loglh = _precision_model = _precision_brlen = prec;
      break;
    default:
      assert(0);
  }
}

unsigned int Logging::precision(LogElement elem) const
{
  switch(elem)
  {
    case LogElement::loglh:
      return _precision_loglh;
    case LogElement::model:
      return _precision_model;
    case LogElement::brlen:
      return _precision_brlen;
    case LogElement::all:
      return RAXML_DEFAULT_PRECISION;
    default:
      assert(0);
      return 0;
  }
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
  std::array<char, 128> buffer;
  const auto timeinfo = std::localtime(&t);
  strftime(buffer.data(), sizeof(buffer), "%d-%b-%Y %H:%M:%S", timeinfo);
  logstream << buffer.data();

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
