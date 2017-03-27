#include "file_io.hpp"

using namespace std;

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

  string newick_str;

  std::getline(stream, newick_str);

  pll_utree_t * utree;
  pll_rtree_t * rtree;

  unsigned int tip_count;
  if (!(utree = pll_utree_parse_newick_string(newick_str.c_str(), &tip_count)))
  {
    if (!(rtree = pll_rtree_parse_newick_string(newick_str.c_str(), &tip_count)))
    {
      throw runtime_error("ERROR reading tree file: " + string(pll_errmsg));
    }
    else
    {
  //    LOG_INFO << "NOTE: You provided a rooted tree; it will be automatically unrooted." << endl;
      utree = pll_rtree_unroot(rtree);

      /* optional step if using default PLL clv/pmatrix index assignments */
      pll_utree_reset_template_indices(utree, tip_count);
    }
  }

  tree = Tree(tip_count, utree);

  return stream;
}

NewickStream& operator<<(NewickStream& stream, const BootstrapTree& tree)
{
  stream << tree.pll_utree_start();
  return stream;
}


