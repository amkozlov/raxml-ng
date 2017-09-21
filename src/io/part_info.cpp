#include "file_io.hpp"

using namespace std;

class partition_parser_exception : public runtime_error
{
public:
  partition_parser_exception() : runtime_error("") {};
  partition_parser_exception(const std::string& msg) : runtime_error(msg) {};
};

class empty_line_exception : public partition_parser_exception
{ public: empty_line_exception() : partition_parser_exception() {} };

RaxmlPartitionStream& operator>>(RaxmlPartitionStream& stream, PartitionInfo& part_info)
{
  std::ostringstream strstream;
  std::streambuf * pbuf = strstream.rdbuf();

  bool model_set = false;
  bool eof = false;
  while (!eof)
  {
    int c = stream.get();
    switch (c)
    {
      case ' ':
      case '\t':
        /* ignore whitespace */
        break;
      case '\r':
        /* handle Windows line breaks (\r\n) */
        if (stream.peek() == '\n')
          stream.get();
      case '\n':
      case EOF:
        if (!model_set)
        {
          throw empty_line_exception();
        }
        else
        {
          auto range_str = strstream.str();
          if (!range_str.empty())
          {
            part_info.range_string(range_str);
            eof = true;
          }
          else
            throw partition_parser_exception("Missing range specification!");
        }
        break;
      case ',':
        if (!model_set)
        {
          auto model_str = strstream.str();
          if (!model_str.empty())
          {
            part_info.model(Model(model_str));
            strstream.str("");
            strstream.clear();
            model_set = true;
          }
          else
          {
            throw partition_parser_exception("Missing model specification!");
          }
        }
        else
          pbuf->sputc(c);
        break;
      case '=':
      {
        auto name_str = strstream.str();
        if (!name_str.empty())
        {
          part_info.name(name_str);
          strstream.str("");
          strstream.clear();
        }
        else
          throw partition_parser_exception("Missing name specification!");

        break;
      }
      default:
        pbuf->sputc(c);
    }
  }

  if (part_info.name().empty())
    throw partition_parser_exception("Missing name specification!");
  else if (part_info.range_string().empty())
    throw partition_parser_exception("Missing range specification!");

  return stream;
}

RaxmlPartitionStream& operator>>(RaxmlPartitionStream& stream, PartitionedMSA& parted_msa)
{
  while (stream.peek() != EOF)
  {
    PartitionInfo pinfo;
    try
    {
      stream >> pinfo;
      assert(!pinfo.name().empty() && !pinfo.range_string().empty());
      parted_msa.append_part_info(std::move(pinfo));
    }
    catch (empty_line_exception& e)
    {
      // nothing to do here, just skip the empty line
    }
    catch (partition_parser_exception& e)
    {
      throw runtime_error("Invalid partition definition in row " +
                          to_string(parted_msa.part_count() + 1) + ": " + e.what());
    }
  }
  return stream;
}

RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionInfo& part_info)
{
  stream << part_info.model().to_string(stream.print_model_params()) << ", ";
  stream << part_info.name() << " = ";
  stream.put_range(part_info);
  stream << std::endl;
  return stream;
}

RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionedMSA& parted_msa)
{
  stream.reset();
  for (const auto& pinfo: parted_msa.part_list())
    stream << pinfo;

  return stream;
}



