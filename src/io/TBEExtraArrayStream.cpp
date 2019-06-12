#include "file_io.hpp"

using namespace std;


TBEExtraArrayStream& operator<<(TBEExtraArrayStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  stream << "taxon_id;taxon_transfer_stat\n";
  for (size_t i = 0; i < tree.num_tips(); ++i) {
	  stream << i << ";" << (double) (extra_info->extra_taxa_array[i]) / extra_info->num_close_enough_branches << "\n";
  }
  return stream;
}


