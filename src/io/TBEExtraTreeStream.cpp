#include "file_io.hpp"

using namespace std;


TBEExtraTreeStream& operator<<(TBEExtraTreeStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  const std::vector<pll_unode_t*> split_node_map = tree.get_split_node_map();
  //...

  tree.pll_utree();

  /*auto print_cb = stream.brlens() ? newick_print_cb : newick_name_cb;
  char * newick_str = pll_utree_export_newick(&root, print_cb);
  if (newick_str)
  {
    stream << newick_str << std::endl;
    free(newick_str);
  }
  else
  {
    assert(pll_errno);
    libpll_check_error("Failed to generate Newick");
  }*/
  return stream;
}


