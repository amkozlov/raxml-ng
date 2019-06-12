#include "file_io.hpp"

using namespace std;


TBEExtraArrayStream& operator<<(TBEExtraArrayStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  stream << "taxon_label;taxon_transfer_stat\n";
  for (size_t i = 0; i < tree.num_tips(); ++i) {
	  stream << tree.tip_labels_list()[i] << ";" << (double) (extra_info->extra_taxa_array[i]) / (double) extra_info->num_bs_trees << "\n";
  }
  return stream;
}


