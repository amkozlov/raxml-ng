#ifndef RAXML_FILE_IO_HPP_
#define RAXML_FILE_IO_HPP_

#include "Tree.hpp"
#include <fstream>

class NewickStream : public std::fstream
{
public:
  NewickStream(std::string fname) : std::fstream(fname, std::ios::out) {};
};

class RaxmlPartitionFileStream : public std::fstream
{
public:
  RaxmlPartitionFileStream(std::string fname) : std::fstream(fname, std::ios::in) {};
};

NewickStream& operator<<(NewickStream& stream, const pll_utree_t& tree)
{
  char * newick_str = pll_utree_export_newick(&tree);
  stream << newick_str << std::endl;
  free(newick_str);
  return stream;
}

NewickStream& operator<<(NewickStream& stream, const Tree& tree)
{
  stream << tree.pll_utree_start();
  return stream;
}

NewickStream& operator>>(NewickStream& stream, Tree& tree)
{
//  stream.getline()
//  char * newick_str = pll_utree_export_newick((pll_utree_t *) &tree);
//  stream << newick_str << std::endl;
//  free(newick_str);

  tree.fix_missing_brlens();
  assert(0);
  return stream;
}

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

#endif /* RAXML_FILE_IO_HPP_ */
