#include "EbgSupportTree.hpp"
#include "../topology/RFDistCalculator.hpp"

#include "ebg.h"

EbgSupportTree::EbgSupportTree(const Tree& tree, const TreeList& pars_trees, const TreeList& pars_boot_trees):
  BootstrapTree(tree), _ps_tree(tree), _pbs_tree(tree), _pbs_avg_rrf(-1.), _pbs_skewness(0.)
{
  if (!pars_trees.empty())
    add_parsimony_trees(pars_trees);
  if (!pars_boot_trees.empty())
    add_parsimony_boostrap_trees(pars_boot_trees);
}

EbgSupportTree::EbgSupportTree(const Tree& tree): EbgSupportTree(tree, TreeList(), TreeList())
{}


static double skew(const doubleVector& v)
{
  double sk = 0.;

  if (!v.empty())
  {
    double N = v.size();
    double mean = std::accumulate(v.cbegin(), v.cend(), 0.) / N;
    double m2 = 0.;
    double m3 = 0.;

    for (size_t i = 0; i < N; ++i)
    {
      double d = v[i] - mean;
      double d2 = d * d;

      m2 += d2;
      m3 += d2 * d;
    }

    sk = sqrt(N) * m3 / (m2 * sqrt(m2));
  }

  return sk;
}

void EbgSupportTree::add_parsimony_trees(const TreeList& treelist)
{
  for (const auto& tree: treelist)
  {
    _ps_tree.add_replicate_tree(tree);
  }
  _ps_tree.compute_support();
}

void EbgSupportTree::add_parsimony_boostrap_trees(const TreeList& treelist)
{
  for (const auto& tree: treelist)
  {
    _pbs_tree.add_replicate_tree(tree);
  }
  _pbs_tree.compute_support();

  _pbs_skewness = skew(_pbs_tree.support());

  RFDistCalculator dist_calculator(treelist);
  _pbs_avg_rrf = dist_calculator.avg_rrf();
}

bool EbgSupportTree::compute_support()
{
//   using namespace ebg;
   ebg_light_features features;

   double total_brlen = sum_of_brlens(false);
   const auto& ps_support = _ps_tree.support();
   const auto& pbs_support = _pbs_tree.support();

   // set global tree-level features
   features.mean_norm_rf_distance = _pbs_avg_rrf;
   features.skewness_bootstrap_pars_support_tree = _pbs_skewness;

   printf("avg_rrf: %lf, pbs_skew: %lf, total_brlen: %lf\n",
          features.mean_norm_rf_distance, features.skewness_bootstrap_pars_support_tree, total_brlen);

  _support.resize(_pll_splits_hash->entry_count);

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      const corax_unode_t *node = !_node_split_map.empty() ? _node_split_map[e->bip_number] :
          _pll_utree->nodes[_pll_utree->tip_count + e->bip_number];

      // set branch-level features
      features.branch_id = e->bip_number;
      features.parsimony_support = ps_support.at(features.branch_id);
      features.parsimony_bootstrap_support = pbs_support.at(features.branch_id);
      features.branch_length = node->length;
      features.norm_branch_length = features.branch_length / total_brlen;
      double support = ebg_predict_branch_support(&features);
      _support[e->bip_number] = support;

      printf("branch_id: %u, support: %lf, brlen: %lf, norm_brlen: %lf, ps: %lf, pbs: %lf\n",
             features.branch_id, support, features.branch_length, features.norm_branch_length,
             features.parsimony_support, features.parsimony_bootstrap_support);
      e = e->next;
    }
  }

  return true;
}



EbgSupportTree::~EbgSupportTree()
{
}

