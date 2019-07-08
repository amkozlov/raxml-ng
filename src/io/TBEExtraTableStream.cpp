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
  stream << "Edge\tSupport\t";
  for (size_t i = 0; i < tree.num_tips(); ++i) {
          stream << tree.tip_labels_list()[i];
          if (i < tree.num_tips() - 1) {
                  stream << "\t";
          } else {
                  stream << "\n";
          }
  }

  auto bufsize = tree.num_tips() * 10;
  char * buf = new char[bufsize];
  auto support = tree.get_support();
  for (size_t i = 0; i < tree.num_splits(); ++i) {
          stream << tree.get_split_node_map()[i]->clv_index << "\t" << fixed << std::setprecision(6) << support[i];

          char * bufptr = buf;
          for (size_t j = 0; j < tree.num_tips(); ++j)
          {
            double d = (double) (extra_info->extra_taxa_table[i][j]) / divideBy;
            bufptr += sprintf(bufptr, "\t%.6lf", d);
          }
          *bufptr = 0;
          stream << buf << "\n";
  }
  delete[] buf;
  return stream;
}
