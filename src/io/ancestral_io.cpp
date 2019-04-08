#include "file_io.hpp"

using namespace std;

AncestralProbStream& operator<<(AncestralProbStream& stream, const AncestralStates& ancestral)
{
  auto delim = stream.delim();
  stream << fixed << setprecision(stream.precision());

  /* print header line */
  stream << "Node" << delim << "Site" << delim << "State ";
  for (const auto& s: ancestral.state_names)
    stream << delim << "p_" << s;
  stream << endl;

  assert(ancestral.probs.size() == ancestral.num_nodes);
  for (size_t i = 0; i < ancestral.num_nodes; ++i)
  {
    string node_name = i < ancestral.node_names.size() ?
                          ancestral.node_names.at(i) : ("Node" + to_string(i+1));
    const auto& probvec = ancestral.probs.at(i);
    const auto& seq = ancestral.ml_state_seq(i);

    assert(probvec.size() == ancestral.num_sites * ancestral.num_states);

    auto prob = probvec.cbegin();
    for (size_t j = 0; j < ancestral.num_sites; ++j)
    {
      stream << node_name << delim << (j+1) << delim << seq[j];
      for (size_t k = 0; k < ancestral.num_states; ++k)
        stream << delim << *prob++;
      stream << endl;
    }
  }
  return stream;
}

AncestralStateStream& operator<<(AncestralStateStream& stream, const AncestralStates& ancestral)
{
  auto delim = stream.delim();
  stream << fixed << setprecision(stream.precision());

  assert(ancestral.probs.size() == ancestral.num_nodes);
  for (size_t i = 0; i < ancestral.num_nodes; ++i)
  {
    string node_name = i < ancestral.node_names.size() ?
                          ancestral.node_names.at(i) : ("Node" + to_string(i));
    const auto& seq = ancestral.ml_state_seq(i);

    stream << node_name << delim << seq << endl;
  }
  return stream;
}
