#include "file_io.hpp"

#if defined __MINGW32__
#define asprintf __mingw_asprintf
#endif

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
  if (asprintf(&newick, "%s:%.*lf",
           node->label ? node->label : "" , precision, node->length) < 0)
    return NULL;

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
  if (newick_str)
  {
    stream << newick_str << std::endl;
    free(newick_str);
  }
  else
  {
    assert(pll_errno);
    libpll_check_error("Failed to generate Newick");
  }
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

  std::getline(stream, newick_str, ';');

  // discard any trailing spaces, newlines etc.
  stream >> std::ws;

  if (!newick_str.empty())
  {
    newick_str += ";";

    pll_utree_t * utree = pll_utree_parse_newick_string_unroot(newick_str.c_str());

    libpll_check_error("ERROR reading tree file");

    assert(utree);

    tree = Tree(*utree);

    pll_utree_destroy(utree, nullptr);
  }

  return stream;
}

NewickStream& operator<<(NewickStream& stream, const BootstrapTree& tree)
{
  stream << tree.pll_utree_root();
  return stream;
}


