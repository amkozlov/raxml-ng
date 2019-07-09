#include "file_io.hpp"

using namespace std;


TBEExtraArrayStream& operator<<(TBEExtraArrayStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  stream << "Taxon\ttIndex\n";
  auto tip_labels_list = tree.tip_labels_list();
  for (size_t i = 0; i < tree.num_tips(); ++i) {
	  stream << tip_labels_list[i] << "\t" << (double) (extra_info->extra_taxa_array[i] * 100) / (double) extra_info->num_bs_trees << "\n";
  }
  return stream;
}


