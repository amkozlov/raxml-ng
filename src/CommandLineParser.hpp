#ifndef SRC_COMMANDLINEPARSER_HPP_
#define SRC_COMMANDLINEPARSER_HPP_

#include "Options.hpp"

class OptionException : public RaxmlException
{
public:
  OptionException(const std::string& message)
  : RaxmlException(message)
  {
  }
};


class InvalidOptionValueException : public OptionException
{
public:
  InvalidOptionValueException(const std::string& message) : OptionException(message) {}

  InvalidOptionValueException(const std::string& format, const std::string& value) :
    OptionException("")
  {
    _message.reserve(format.size() + value.size());
    sprintf(&_message[0], format.c_str(), value.c_str());
  }
};

class CommandLineParser
{
public:
  CommandLineParser() {};
  ~CommandLineParser() = default;

  void parse_options(int argc, char** argv, Options &opts);
  void print_help();
};

#endif /* SRC_COMMANDLINEPARSER_HPP_ */
