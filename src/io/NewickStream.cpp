#include "file_io.hpp"

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



