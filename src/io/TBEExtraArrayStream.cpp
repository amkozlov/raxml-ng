#include "file_io.hpp"

using namespace std;


TBEExtraArrayStream& operator<<(NewickStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  //...

  auto print_cb = stream.brlens() ? newick_print_cb : newick_name_cb;
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
  }
  return stream;
}


