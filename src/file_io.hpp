#ifndef RAXML_FILE_IO_HPP_
#define RAXML_FILE_IO_HPP_

#include "Tree.hpp"
#include <fstream>

class NewickStream : public std::fstream
{
public:
  NewickStream(std::string fname) : std::fstream(fname, std::ios::out) {};
};

NewickStream& operator<<(NewickStream& stream, const pll_utree_t& tree)
{
  // TODO: fix in libpll
  char * newick_str = pll_utree_export_newick((pll_utree_t *) &tree);
  stream << newick_str << std::endl;
  free(newick_str);
  return stream;
}


#endif /* RAXML_FILE_IO_HPP_ */
