#include "file_io.hpp"

std::fstream& operator>>(std::fstream& stream, PartitionInfo& part_info)
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
      case '\n':
      case EOF:
        part_info.range_string(strstream.str());
        eof = true;
        break;
      case ',':
        if (!model_set)
        {
          part_info.model(Model(strstream.str()));
          strstream.str("");
          strstream.clear();
          model_set = true;
        }
        else
          pbuf->sputc(c);
        break;
      case '=':
        part_info.name(strstream.str());
        strstream.str("");
        strstream.clear();
        break;
      default:
        pbuf->sputc(c);
    }
  }

  return stream;
}

std::fstream& operator>>(std::fstream& stream, PartitionedMSA& parted_msa)
{
  while (stream.peek() != EOF)
  {
    PartitionInfo pinfo;
    stream >> pinfo;
    parted_msa.append_part_info(std::move(pinfo));
  }
  return stream;
}



