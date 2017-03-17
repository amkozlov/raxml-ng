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
  PhylipStream(const std::string& fname) : MSAFileStream(fname) {}
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


class RaxmlPartitionFileStream : public std::fstream
{
public:
  RaxmlPartitionFileStream(std::string fname) : std::fstream(fname, std::ios::in) {};
};

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

std::fstream& operator>>(std::fstream& stream, PartitionInfo& part_info);
std::fstream& operator>>(std::fstream& stream, PartitionedMSA& parted_msa);

#endif /* RAXML_FILE_IO_HPP_ */
