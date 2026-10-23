#include "file_io.hpp"
using namespace std;

FileIOStream& operator<<(FileIOStream& stream, const AuTest& au_test)
{
  auto delim = stream.delim();
  stream << fixed << setprecision((int) stream.precision());

  auto p_values = au_test.get_p_values();

  stream << "TreeID" << delim << "p-AU" << delim << "Plausible" << endl;
  for (unsigned int tree_num = 0; tree_num < p_values.size(); tree_num++)
  {
    stream << (tree_num+1) << delim << p_values[tree_num] << delim
           << (au_test.is_plausible(tree_num) ? "+" : "-") << endl;
  }

  return stream;
}
