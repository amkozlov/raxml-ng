#ifndef RAXML_FILE_IO_HPP_
#define RAXML_FILE_IO_HPP_

#include <fstream>

#include "../Tree.hpp"
#include "../bootstrap/BootstrapTree.hpp"

class NewickStream : public std::fstream
{
public:
  NewickStream(std::string fname) : std::fstream(fname, std::ios::out) {};
  NewickStream(std::string fname, std::ios_base::openmode mode) :
    std::fstream(fname, mode) {};
};

class MSAFileStream
{
public:
  MSAFileStream(const std::string& fname) :
    _fname(fname) {}

  const std::string& fname() const { return _fname; };

private:
  std::string _fname;
};

class PhylipStream : public MSAFileStream
{
public:
  PhylipStream(const std::string& fname, bool interleaved = true) :
    MSAFileStream(fname), _interleaved(interleaved) {}

  bool interleaved() const { return _interleaved; }
private:
  bool _interleaved;
};

class FastaStream : public MSAFileStream
{
public:
  FastaStream(const std::string& fname) : MSAFileStream(fname) {}
};

class CATGStream : public MSAFileStream
{
public:
  CATGStream(const std::string& fname) : MSAFileStream(fname) {}
};


class RaxmlPartitionStream : public std::fstream
{
public:
  RaxmlPartitionStream(std::string fname, bool use_range_string = false) :
    std::fstream(fname, std::ios::out), _offset(0), _print_model_params(false),
    _use_range_string(use_range_string) {}
  RaxmlPartitionStream(std::string fname, std::ios_base::openmode mode) :
    std::fstream(fname, mode), _offset(0), _print_model_params(false), _use_range_string(false) {}

  bool print_model_params() const { return _print_model_params; }
  void print_model_params(bool value) { _print_model_params = value; }

  void reset() { _offset = 0; }
  void put_range(const PartitionInfo& part_info)
  {
    if (_use_range_string && !part_info.range_string().empty())
      *this << part_info.range_string();
    else
    {
      auto part_len = part_info.msa().length();
      *this << (_offset+1) << "-" << (_offset+part_len);
      _offset += part_len;
    }
  }

private:
  size_t _offset;
  bool _print_model_params;
  bool _use_range_string;
};

NewickStream& operator<<(NewickStream& stream, const pll_unode_t& root);
NewickStream& operator<<(NewickStream& stream, const pll_utree_t& tree);
NewickStream& operator<<(NewickStream& stream, const Tree& tree);
NewickStream& operator>>(NewickStream& stream, Tree& tree);

NewickStream& operator<<(NewickStream& stream, const BootstrapTree& tree);
//NewickStream& operator>>(NewickStream& stream, BootstrapTree& tree);

PhylipStream& operator>>(PhylipStream& stream, MSA& msa);
FastaStream& operator>>(FastaStream& stream, MSA& msa);
CATGStream& operator>>(CATGStream& stream, MSA& msa);
MSA msa_load_from_file(const std::string &filename, const FileFormat format);

PhylipStream& operator<<(PhylipStream& stream, MSA& msa);
PhylipStream& operator<<(PhylipStream& stream, PartitionedMSA& msa);

RaxmlPartitionStream& operator>>(RaxmlPartitionStream& stream, PartitionInfo& part_info);
RaxmlPartitionStream& operator>>(RaxmlPartitionStream& stream, PartitionedMSA& parted_msa);

RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionInfo& part_info);
RaxmlPartitionStream& operator<<(RaxmlPartitionStream& stream, const PartitionedMSA& parted_msa);

std::string to_newick_string_rooted(const Tree& tree, double root_brlen = 0.0);

#endif /* RAXML_FILE_IO_HPP_ */
