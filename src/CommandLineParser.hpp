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

private:
  void compute_num_searches(Options &opts);
  void check_options(Options &opts);
  void parse_start_trees(Options &opts, const std::string& arg);
};

#endif /* SRC_COMMANDLINEPARSER_HPP_ */
