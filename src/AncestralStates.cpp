#include "AncestralStates.hpp"

using namespace std;

AncestralStates::AncestralStates(size_t nodes, size_t states, size_t sites) :
    num_nodes(nodes), num_states(states), num_sites(sites),
    ambiguity(true)
{
  prob_eps = num_states > 0 ? 0.5 / num_states : 0.1;
}

std::string AncestralStates::ml_state(size_t node_idx, size_t site_idx) const
{
  if (node_idx >= num_nodes)
    throw runtime_error("AncestralStates: Node index out of bounds");

  if (site_idx >= num_sites)
    throw runtime_error("AncestralStates: Site index out of bounds");

  const auto& probvec = probs.at(node_idx);

  assert(probvec.size() == num_sites * num_states);

  auto prob = probvec.cbegin() + site_idx * num_states;
  size_t mstate = 0;
  for (size_t k = 1; k < num_states; ++k)
  {
    if (prob[k] > prob[mstate])
      mstate = k;
  }

  if (ambiguity)
  {
    pll_state_t astate = 0;
    pll_state_t state = 1;

    for (size_t k = 0; k < num_states; ++k)
    {
      if (prob[k] + prob_eps > prob[mstate])
        astate |= state;
      state <<= 1;
    }

    return state_namemap.count(astate) ? state_namemap.at(astate) : state_names[mstate];
  }
  else
    return state_names[mstate];  // TviODO: check for gap
}

std::string AncestralStates::ml_state_seq(size_t node_idx) const
{
  string s;

  s.reserve(num_sites);

  for (size_t k = 0; k < num_sites; ++k)
    s += ml_state(node_idx, k);

  return s;
}
