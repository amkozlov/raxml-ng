#include "GCFSupportTree.hpp"

GCFSupportTree::GCFSupportTree (const Tree& tree) : SupportTree(tree),
  _num_decisive_trees(tree.num_splits(), 0)
{
}

GCFSupportTree::~GCFSupportTree ()
{
}

/* induced split = reference split reduced to a subset of taxa present in the respective gene tree */
static corax_split_t induced_split(corax_split_t ref_split, IDVector id_map)
{
  uintVector tip_ids;
  unsigned int split_size   = sizeof(corax_split_base_t) * 8;

  tip_ids.reserve(id_map.size());
  for (unsigned int i = 0; i < id_map.size(); ++i)
  {
    auto ref_id = id_map[i];
    unsigned int elem   = ref_id / split_size;
    unsigned int offset = ref_id % split_size;

    if (ref_split[elem] & (1u << offset))
     tip_ids.push_back(i);
  }
  return corax_utree_split_from_tips(tip_ids.data(), tip_ids.size(), id_map.size());
}

void GCFSupportTree::add_replicate_tree(const Tree& tree)
{
  auto gene_tip_count = tree.num_tips();

  PllSplitSharedPtr splits(corax_utree_split_create((corax_unode_t*) &tree.pll_utree_root(),
                                                    tree.num_tips(),
                                                    nullptr),
                           corax_utree_split_destroy);

  bitv_hashtable_t * gene_splits_hash = corax_utree_split_hashtable_insert(nullptr,
                                                         splits.get(),
                                                         gene_tip_count,
                                                         tree.num_splits(),
                                                         nullptr,
                                                         false);

  // map taxon ids between reference tree and gene tree
  auto ref_id_map = tip_ids();
  auto gene_id_map = tree.tip_ids();

  IDVector gene2ref_id_map(gene_id_map.size());
  for (const auto& e: gene_id_map)
  {
    try
    {
      auto ref_tip_id = ref_id_map.at(e.first);
      gene2ref_id_map[e.second] = ref_tip_id;
    }
    catch (std::out_of_range&)
    {
      throw InvalidReplicateTreeException("Taxon not found in reference tree: " + e.first);
    }
  }

  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      auto ref_split = e->bit_vector;
      auto ind_split = induced_split(ref_split, gene2ref_id_map);

      auto ls = corax_utree_split_lightside(ind_split, gene_tip_count);

//      if (e->bip_number == 44)
//        printf("tree # %5lu, bip: %5u,  lightside: %5u\n", _num_bs_trees, e->bip_number, ls);

      /* a replicate tree is decisive if each side of the induced split has at least 2 taxa */
      bool decisive = ls > 1;
      if (decisive)
      {
        // increment number of decisive replicate trees for this branch
        _num_decisive_trees[e->bip_number]++;

        // check if reference tree split is concordant with replicate tree
        if (corax_utree_split_hashtable_lookup(gene_splits_hash, ind_split, gene_tip_count))
          corax_utree_split_hashtable_insert_single(_pll_splits_hash, ref_split, 1.0);
      }

      e = e->next;
    }
  }

  corax_utree_split_hashtable_destroy(gene_splits_hash);

  _num_bs_trees++;
}

bool GCFSupportTree::compute_support()
{
  for (unsigned int i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      /* normalize support by the number of decisive trees */
      auto num_trees = _num_decisive_trees[e->bip_number];
      if (num_trees > 0)
        e->support /= num_trees;
//      printf("bip: %5u,  # decisive trees: %5u, support: %lf,  brlen: %lf\n",
//             e->bip_number, num_trees, e->support, _node_split_map[e->bip_number]->length);
      e = e->next;
    }
  }

  collect_support();

  return true;
}



