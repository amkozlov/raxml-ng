#include "file_io.hpp"

using namespace std;

char * newick_name_cb(const pll_unode_t * node)
{
  return node->label ? strdup(node->label) : strdup("");
}

char * newick_print_cb(const pll_unode_t * node)
{
  // that's ugly, but cannot find a better solution so far...
  const unsigned int precision = logger().precision(LogElement::brlen);

  char * newick;
  asprintf(&newick, "%s:%.*lf",
           node->label ? node->label : "" , precision, node->length);
  return newick;
}

std::string to_newick_string_rooted(const Tree& tree, double root_brlen)
{
  char * newick_str = pll_utree_export_newick_rooted(&tree.pll_utree_root(),
                                                     root_brlen);
  std::string result = newick_str;
  free(newick_str);
  return result;
}

NewickStream& operator<<(NewickStream& stream, const pll_unode_t& root)
{
  char * newick_str = pll_utree_export_newick(&root, newick_print_cb);
  stream << newick_str << std::endl;
  free(newick_str);
  return stream;
}

NewickStream& operator<<(NewickStream& stream, const pll_utree_t& tree)
{
  stream << *tree.vroot;
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
      pll_utree_reset_template_indices(utree->vroot, utree->tip_count);
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


