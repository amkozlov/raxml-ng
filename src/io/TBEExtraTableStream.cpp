#include "file_io.hpp"

using namespace std;


TBEExtraTableStream& operator<<(TBEExtraTableStream& stream, const TransferBootstrapTree& tree)
{
  pllmod_tbe_extra_info_t* extra_info = tree.get_extra_info();
  if (!extra_info) {
	  throw std::runtime_error("Extra info is null");
  }
  if (!extra_info->extra_taxa_table) {
	  throw std::runtime_error("Extra taxa table is null");
  }
  double divideBy = extra_info->num_bs_trees * tree.num_splits();
  for (size_t i = 0; i < tree.num_tips(); ++i) {
	  for (size_t j = 0; j < tree.num_splits(); ++j) {
		  stream << fixed << std::setprecision(10) << (double) (extra_info->extra_taxa_table[j][i]) / divideBy;
		  if (j < tree.num_splits() - 1) {
			  stream << "\t";
		  }
	  }
	  stream << "\n";
  }
  return stream;
}
