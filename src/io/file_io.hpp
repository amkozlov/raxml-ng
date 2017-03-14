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


std::fstream& operator>>(std::fstream& stream, PartitionInfo& part_info);
std::fstream& operator>>(std::fstream& stream, PartitionedMSA& parted_msa);

#endif /* RAXML_FILE_IO_HPP_ */
