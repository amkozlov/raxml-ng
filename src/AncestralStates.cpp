#include "AncestralStates.hpp"

using namespace std;

AncestralStates::AncestralStates(size_t nodes, size_t states, size_t sites) :
    num_nodes(nodes), num_states(states), ambiguity(true)
{
  part_num_sites.push_back(sites);
  prob_eps = num_states > 0 ? 0.5 / num_states : 0.1;
}

AncestralStates::AncestralStates(size_t nodes, const std::shared_ptr<PartitionedMSA>& part_msa) :
    parted_msa(part_msa), num_nodes(nodes), ambiguity(true)
{
  const Model& model = part_msa->part_info(0).model();
  num_states = model.num_states();
  state_names = model.state_names();
  state_namemap = model.full_state_namemap();

  for (const auto& pinfo: part_msa->part_list())
  {
    part_num_sites.push_back(pinfo.msa().num_sites());
    if (pinfo.model().data_type() != model.data_type())
      throw runtime_error("Ancestral State Reconstruction is not supported for mixed-type alignments (eg DNA and AA).");
  }

  // TODO move out of here?
  allocate_probs();

  prob_eps = 0.5 / num_states;
}

void AncestralStates::allocate_probs()
{
  probs.clear();
  probs.resize(part_num_sites.size());
  for (size_t p = 0; p < part_num_sites.size(); ++p)
  {
    size_t part_span = part_num_sites[p] * num_states;
    for (size_t n = 0; n < num_nodes; ++n)
    {
      probs[p].emplace_back(part_span);
    }
  }
}

size_t AncestralStates::num_parts() const
{
  return part_num_sites.size();
}

std::string AncestralStates::ml_state(doubleVector::const_iterator& prob) const
{
  size_t mstate = 0;
  for (size_t k = 1; k < num_states; ++k)
  {
    if (prob[k] > prob[mstate])
      mstate = k;
  }

  pll_state_t astate = 0;
  pll_state_t state = 1;

  for (size_t k = 0; k < num_states; ++k)
  {
    if (prob[k] + prob_eps > prob[mstate])
      astate |= state;
    state <<= 1;
  }

  if (ambiguity)
    return state_namemap.count(astate) ? state_namemap.at(astate) : state_names[mstate];
  else
    return PLL_STATE_POPCNT(astate) > 1 ? "-" : state_names[mstate];
}

const doubleVector& AncestralStates::node_prob_vector(size_t node_idx, size_t part_idx) const
{
  if (part_idx >= part_num_sites.size())
    throw runtime_error("AncestralStates: Partition index out of bounds: " + to_string(part_idx));

  if (node_idx >= num_nodes)
    throw runtime_error("AncestralStates: Node index out of bounds");

  const auto& probvec = probs.at(part_idx).at(node_idx);

  assert(probvec.size() == part_num_sites[part_idx] * num_states);

  return probvec;
}

std::string AncestralStates::ml_state(size_t node_idx, size_t site_idx, size_t part_idx) const
{
  if (site_idx >= part_num_sites[part_idx])
    throw runtime_error("AncestralStates: Site index out of bounds");

  const auto& probvec = node_prob_vector(node_idx, part_idx);
  auto prob = probvec.cbegin() + site_idx * num_states;
  return ml_state(prob);
}

std::string AncestralStates::ml_state_seq(const std::string& node_name, size_t part_idx) const
{
  if (node_namemap.count(node_name))
    return ml_state_seq(node_namemap.at(node_name), part_idx);
  else
    throw runtime_error("AncestralStates: Internal node not found: " + node_name);
}

std::string AncestralStates::ml_state_seq(size_t node_idx, size_t part_idx) const
{
  const auto& probvec = node_prob_vector(node_idx, part_idx);
  auto num_sites = part_num_sites[part_idx];

  return ml_state_seq(probvec, num_sites);
}

std::string AncestralStates::ml_state_seq(const doubleVector& probvec, size_t num_sites) const
{
  string s;
  s.resize(num_sites);

  auto prob = probvec.cbegin();
  for (size_t k = 0; k < num_sites; ++k)
  {
    s[k] = ml_state(prob)[0];
    prob += num_states;
  }

  return s;
}

std::string AncestralStates::ml_state_tipseq(const std::string& tip_name, size_t part_idx) const
{
  if (part_idx >= parted_msa->part_count())
    throw runtime_error("AncestralStates: Partition index out of bounds: " + to_string(part_idx));

  if (!parted_msa->taxon_id_map().count(tip_name))
    throw runtime_error("AncestralStates: tip node not found: " + tip_name);

  size_t taxon_id = parted_msa->taxon_id_map().at(tip_name);
  const auto& pinfo = parted_msa->part_info(part_idx);
  const auto& errm = pinfo.model().error_model();

  if (errm)
  {
    doubleVector tmp_clv;
    pinfo.fill_tip_clv(taxon_id, tmp_clv);
    return ml_state_seq(tmp_clv, part_num_sites[part_idx]);
  }
  else
    return pinfo.msa().at(taxon_id);
}

void assign_tree(AncestralStates& ancestral, const pllmod_ancestral_t& pll_ancestral)
{
  if (!ancestral.num_nodes)
    ancestral.num_nodes = pll_ancestral.node_count;
  else if (ancestral.num_nodes != pll_ancestral.node_count)
  {
    throw runtime_error("Incompatible pll_ancestral size: " + to_string(pll_ancestral.node_count) +
                        " (expected: " + to_string(ancestral.num_nodes) + ")");

  }

  ancestral.tree = Tree(*pll_ancestral.tree);
  ancestral.node_names.clear();
  for (size_t i = 0; i < pll_ancestral.node_count; ++i)
  {
    auto name = pll_ancestral.nodes[i]->label;
    ancestral.node_namemap[name] = ancestral.node_names.size();
    ancestral.node_names.push_back(name);
  }
}

void assign_probs(AncestralStates& ancestral, const pllmod_ancestral_t& pll_ancestral,
                  const PartitionAssignment& part_assign)
{
  if (ancestral.num_nodes != pll_ancestral.node_count)
  {
    throw runtime_error("Incompatible pll_ancestral size: " + to_string(pll_ancestral.node_count) +
                        " (expected: " + to_string(ancestral.num_nodes) + ")");

  }

  if (ancestral.probs.empty())
    ancestral.allocate_probs();

  size_t pll_offset = 0;
  for (size_t i = 0; i <  pll_ancestral.partition_count; ++i)
  {
    unsigned int p = pll_ancestral.partition_indices[i];
    PartitionAssignment::const_iterator part_range = part_assign.find(p);

    if (part_range == part_assign.end())
      throw runtime_error("Partition " + to_string(p) + " not found in part_assign!" );

    auto& part_probs = ancestral.probs.at(p);
    size_t prob_offset = part_range->start * ancestral.num_states;
    size_t anc_span = part_range->length * ancestral.num_states;

    for (size_t n = 0; n < pll_ancestral.node_count; ++n)
    {
      double * probs = part_probs.at(n).data() + prob_offset;
      double * pll_probs = pll_ancestral.probs[n] + pll_offset;

      memcpy(probs, pll_probs, anc_span * sizeof(double));
    }
    pll_offset += anc_span;
  }
}
