#ifndef SRC_COMMANDLINEPARSER_HPP_
#define SRC_COMMANDLINEPARSER_HPP_

#include "Options.hpp"

class OptionException : public std::exception
{
public:
  OptionException(const std::string& message)
  : message(message)
  {
  }

virtual const char*
  what() const noexcept
  {
    return message.c_str();
  }

protected:
  std::string message;
};


class InvalidOptionValueException : public OptionException
{
public:
  InvalidOptionValueException(const std::string& format, const std::string& value) :
    OptionException("")
  {
    message.reserve(format.size() + value.size());
    sprintf(&message[0], format.c_str(), value.c_str());
  }
};

class CommandLineParser
{
public:
  CommandLineParser(int argc, char** argv) : argc(argc), argv(argv) {};
  ~CommandLineParser() = default;

  void parse_options(Options &opts);
  void print_help();

private:
  int argc;
  char** argv;
};

#endif /* SRC_COMMANDLINEPARSER_HPP_ */
