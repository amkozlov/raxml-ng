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
        /* fall through */
      case '\n':
      case EOF:
        if (!model_set)
        {
          string str = strstream.str();
          str.erase(std::remove_if(str.begin(), str.end(),
                                   [](unsigned char x){return std::isspace(x);}),
                     str.end());
          if (str.empty())
            throw empty_line_exception();
          else
          {
            throw partition_parser_exception("Invalid partition format: " +
                                                        string(strstream.str()));
          }
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
  if (!parted_msa.part_count())
  {
    throw runtime_error("Partition file is empty!");
  }
  return stream;
}

RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionInfo& part_info)
{
  stream << part_info.model().to_string(stream.print_model_params(), stream.precision()) << ", ";
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

RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionedMSAView& parted_msa)
{
  stream.reset();
  size_t offset = 0;
  for (size_t p = 0; p < parted_msa.part_count(); ++p)
  {
    auto model_str = parted_msa.part_model(p).to_string(stream.print_model_params(),
                                                        stream.precision());
    auto part_name = parted_msa.part_name(p);
    auto part_len = parted_msa.part_sites(p);

    stream << model_str << ", "
           << part_name << " = "
           << (offset+1) << "-" << (offset+part_len)
           << std::endl;
    offset += part_len;
  }
  assert(offset == parted_msa.total_sites());

  return stream;
}



