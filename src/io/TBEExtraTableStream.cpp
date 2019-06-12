#include "file_io.hpp"

using namespace std;


TBEExtraTableStream& operator<<(TBEExtraTableStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  for (size_t i = 0; i < tree.num_tips(); ++i) {
	  for (size_t j = 0; j < tree.num_splits(); ++i) {
		  stream << (double) (extra_info->extra_taxa_table[j][i]) / extra_info->num_bs_trees;
		  if (j < tree.num_splits() - 1) {
			  stream << "\t";
		  }
	  }
	  stream << "\n";
  }
  return stream;
}


