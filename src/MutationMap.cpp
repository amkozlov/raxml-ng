#include "MutationMap.hpp"

using namespace std;

MutationMap::MutationMap(const AncestralStates& ancestral, const PartitionedMSA& pmsa)
{
  init(ancestral, pmsa);
}

void MutationMap::init(const AncestralStates& ancestral, const PartitionedMSA& pmsa)
{
  // partitioned alignments not supported yet!
  assert(pmsa.part_count() == 1);
  const auto& msa = pmsa.full_msa();
  auto charmap = pmsa.model(0).charmap();

  tree = ancestral.tree;
  mut_names = msa.site_names();

  mut_list.resize(tree.num_branches());

  for (size_t i = 0; i < tree.pll_utree().inner_count + tree.pll_utree().tip_count; ++i)
  {
    auto node1 = tree.pll_utree().nodes[i];
    auto node2 = node1->back;
    auto branch_id = node1->pmatrix_index;
    assert(node1->pmatrix_index == node2->pmatrix_index);
    if (mut_list[branch_id].empty())
    {
      string seq1 = pllmod_utree_is_tip(node1) ? ancestral.ml_state_tipseq(node1->label) :
                                                 ancestral.ml_state_seq(node1->label);
      string seq2 = pllmod_utree_is_tip(node2) ? ancestral.ml_state_tipseq(node2->label) :
                                                 ancestral.ml_state_seq(node2->label);
      assert(seq1.length() == seq2.length());
      for (size_t j = 0; j < seq1.length(); ++j)
      {
        /* we call mutations very conservatively, excluding gaps/ambiguities, eg for DNA:
         * mutation:     A<->C, R<->Y
         * no mutation:  A<->N, A<->R */
        auto s1 = charmap[(int) seq1[j]];
        auto s2 = charmap[(int) seq2[j]];
        if ((s1 & s2) == 0)
          mut_list[branch_id].push_back(j);
      }
    }
  }
}

