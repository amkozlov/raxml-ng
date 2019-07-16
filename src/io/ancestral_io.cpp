#include "file_io.hpp"

using namespace std;

AncestralProbStream& operator<<(AncestralProbStream& stream, const AncestralStates& ancestral)
{
  auto delim = stream.delim();
  stream << fixed << setprecision(stream.precision());

  auto num_parts = ancestral.num_parts();

  /* print header line */
  stream << "Node";
  if (num_parts > 1)
    stream << delim << "Part";
  stream << delim << "Site" << delim << "State ";

  for (const auto& s: ancestral.state_names)
    stream << delim << "p_" << s;
  stream << endl;

  assert(ancestral.probs.size() == num_parts);
  for (size_t i = 0; i < ancestral.num_nodes; ++i)
  {
    string node_name = i < ancestral.node_names.size() ?
                          ancestral.node_names.at(i) : ("Node" + to_string(i+1));

    for (size_t p = 0; p < num_parts; ++p)
    {
      auto num_sites = ancestral.part_num_sites[p];
      const auto& probvec = ancestral.probs.at(p).at(i);
      const auto& seq = ancestral.ml_state_seq(i, p);

      assert(probvec.size() == num_sites * ancestral.num_states);

      auto prob = probvec.cbegin();
      for (size_t j = 0; j < num_sites; ++j)
      {
        stream << node_name;
        if (num_parts > 1)
          stream << delim << (p+1);
        stream << delim << (j+1) << delim << seq[j];
        for (size_t k = 0; k < ancestral.num_states; ++k)
          stream << delim << *prob++;
        stream << endl;
      }
    }

  }
  return stream;
}

AncestralStateStream& operator<<(AncestralStateStream& stream, const AncestralStates& ancestral)
{
  auto delim = stream.delim();
  stream << fixed << setprecision(stream.precision());

  auto num_parts = ancestral.num_parts();
  assert(ancestral.probs.size() == num_parts);
  for (size_t i = 0; i < ancestral.num_nodes; ++i)
  {
    string node_name = i < ancestral.node_names.size() ?
                          ancestral.node_names.at(i) : ("Node" + to_string(i));

    stream << node_name << delim;
    for (size_t p = 0; p < num_parts; ++p)
      stream << ancestral.ml_state_seq(i, p);
    stream << endl;
  }
  return stream;
}
