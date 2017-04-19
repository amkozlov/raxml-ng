#include "file_io.hpp"

using namespace std;

NewickStream& operator<<(NewickStream& stream, const pll_unode_t& root)
{
  char * newick_str = pll_utree_export_newick(&root, nullptr);
  stream << newick_str << std::endl;
  free(newick_str);
  return stream;
}

NewickStream& operator<<(NewickStream& stream, const pll_utree_t& tree)
{
  stream << *get_pll_utree_root(&tree);
  return stream;
}

NewickStream& operator<<(NewickStream& stream, const Tree& tree)
{
  stream << tree.pll_utree_root();
  return stream;
}

NewickStream& operator>>(NewickStream& stream, Tree& tree)
{
  string newick_str;

  std::getline(stream, newick_str);

  pll_utree_t * utree;
  pll_rtree_t * rtree;

  if (!(utree = pll_utree_parse_newick_string(newick_str.c_str())))
  {
    if (!(rtree = pll_rtree_parse_newick_string(newick_str.c_str())))
    {
      throw runtime_error("ERROR reading tree file: " + string(pll_errmsg));
    }
    else
    {
  //    LOG_INFO << "NOTE: You provided a rooted tree; it will be automatically unrooted." << endl;
      utree = pll_rtree_unroot(rtree);

      /* optional step if using default PLL clv/pmatrix index assignments */
      pll_utree_reset_template_indices(get_pll_utree_root(utree), utree->tip_count);
    }
  }

  tree = Tree(*utree);

  pll_utree_destroy(utree, nullptr);

  return stream;
}

NewickStream& operator<<(NewickStream& stream, const BootstrapTree& tree)
{
  stream << tree.pll_utree_root();
  return stream;
}


