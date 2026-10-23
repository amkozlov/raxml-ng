#include "file_io.hpp"
using namespace std;

FileIOStream& operator<<(FileIOStream& stream, const AuTest& au_test)
{
  auto delim = stream.delim();
  stream << fixed << setprecision((int) stream.precision());

  /* print header*/
  stream << "TreeID" << delim << "p-AU" << delim << "Plausible" << delim
         << setw(stream.precision()+3) << "LogLH" << delim << "DeltaLH" << endl;

  auto p_values = au_test.get_p_values();

  /* nothing to print -> exit */
  if (p_values.empty())
    return stream;

  /* collect per-tree loglh */
  doubleVector tree_loglh(p_values.size(), -1.);
  for (unsigned int tree_num = 0; tree_num < p_values.size(); tree_num++)
    tree_loglh[tree_num] = au_test.loglh(tree_num);

  double best_loglh = *std::max_element(tree_loglh.cbegin(), tree_loglh.cend());

  for (unsigned int tree_num = 0; tree_num < p_values.size(); tree_num++)
  {
    stream << (tree_num+1) << delim << p_values[tree_num] << delim
           << (au_test.is_plausible(tree_num) ? "+" : "-") << delim
           << tree_loglh[tree_num] << delim
           << (best_loglh - tree_loglh[tree_num]) << delim
           << endl;
  }

  return stream;
}
