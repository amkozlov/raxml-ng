#include "ConstraintTree.hpp"

ConstraintTree::ConstraintTree(const pll_utree_t& pll_utree) : Tree(pll_utree)
{
}

ConstraintTree::~ConstraintTree ()
{
  // TODO Auto-generated destructor stub
}

//ConstraintTree::ConstraintTree (const ConstraintTree &other)
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//ConstraintTree::ConstraintTree (ConstraintTree &&other)
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//ConstraintTree&
//ConstraintTree::operator= (const ConstraintTree &other)
//{
//  // TODO Auto-generated method stub
//
//}
//
//ConstraintTree&
//ConstraintTree::operator= (ConstraintTree &&other)
//{
//  // TODO Auto-generated method stub
//
//}

void ConstraintTree::extract_splits() const
{
  _cons_splits.reset(pllmod_utree_split_create(&pll_utree_root(), _num_tips, nullptr),
                             pllmod_utree_split_destroy);
}

static void truncate_splits(pll_split_t * splits, unsigned int split_count,
                            unsigned int old_tips, unsigned int new_tips)
{
  unsigned int bitv_elem = sizeof(pll_split_base_t) * 8;
  unsigned int bitv_size = new_tips / bitv_elem;
  unsigned int bitv_off = new_tips % bitv_elem;
  if (bitv_off > 0)
    bitv_size++;

  unsigned int mask = 0;
  for (unsigned int i = 0; i < (bitv_off ? bitv_off : bitv_elem); ++i)
    mask |= (1u << i);

  for (unsigned int i = 0; i < split_count; ++i)
  {
    pll_split_t last_elem = splits[i] + bitv_size - 1;
    *last_elem &= mask;
  }
}

bool ConstraintTree::compatible(const Tree& tree) const
{
  extract_splits();

  pll_utree_show_ascii(&pll_utree_root(), PLL_UTREE_SHOW_LABEL | PLL_UTREE_SHOW_BRANCH_LENGTH |
                                       PLL_UTREE_SHOW_CLV_INDEX );

  printf("\n");

  pll_utree_show_ascii(&tree.pll_utree_root(), PLL_UTREE_SHOW_LABEL | PLL_UTREE_SHOW_BRANCH_LENGTH |
                                       PLL_UTREE_SHOW_CLV_INDEX );

  PllSplitSharedPtr check_splits(pllmod_utree_split_create(&tree.pll_utree_root(), tree.num_tips(), nullptr),
                             pllmod_utree_split_destroy);

  if (tree.num_tips() > _num_tips)
  {
    // Tree has free taxa -> adjust splits to ignore them
    truncate_splits(check_splits.get(), tree.num_splits(), tree.num_tips(), _num_tips);
  }

//  printf("comp check: %u %u\n", _num_tips, tree.num_tips());

  bitv_hashtable_t* splits_hash = pllmod_utree_split_hashtable_insert(nullptr,
                                                         check_splits.get(),
                                                         _num_tips,
                                                         tree.num_splits(),
                                                         nullptr,
                                                         0);
//    for (size_t i = 0; i < tree.num_splits(); ++i)
//    {
//      pllmod_utree_split_show(check_splits.get()[i], tree.num_tips());
//      printf("\n");
//    }

    printf("\n");

  for (size_t i = 0; i < num_splits(); ++i)
  {
    pllmod_utree_split_show(_cons_splits.get()[i], _num_tips);
    printf("\n");

    if (!pllmod_utree_split_hashtable_lookup(splits_hash, _cons_splits.get()[i], _num_tips))
      return false;
  }


  return true;
}
