#include "BootstopCheck.hpp"

using namespace std;

BootstopCheck::BootstopCheck(size_t max_bs_trees)
{
  _max_bs_trees = max_bs_trees;
  _num_bs_trees = 0;
  _pll_splits_hash = nullptr;
}

BootstopCheck::~BootstopCheck ()
{
  if (_pll_splits_hash)
    pllmod_utree_split_hashtable_destroy(_pll_splits_hash);
}

void BootstopCheck::add_bootstrap_tree(const Tree& tree)
{
  if (_num_bs_trees == _max_bs_trees)
  {
    throw runtime_error("BootstopCheck::add_bootstrap_tree: "
        "Maximum number of bootstrap trees reached: " + to_string(_max_bs_trees));
  }

  if (!_pll_splits_hash)
    _pll_splits_hash = pllmod_utree_split_hashtable_create(tree.num_tips(), 0);

  if (!_pll_splits_hash)
  {
    assert(pll_errno);
    libpll_check_error("Cannot create split hashtable");
  }

  pll_split_t * splits = pllmod_utree_split_create(&tree.pll_utree_root(),
                                                   tree.num_tips(),
                                                   nullptr);

  assert(_pll_splits_hash);

  for (size_t i = 0; i < tree.num_splits(); ++i)
  {
    bitv_hash_entry_t * e = pllmod_utree_split_hashtable_insert_single(_pll_splits_hash,
                                                                       splits[i],
                                                                       1.0);
    if (!e)
      libpll_check_error("Cannot add a split into hashtable: ");

    assert(e->bip_number <= _split_occurence.size());

    /* new split -> create bit vector with tree occurence flags */
    if (e->bip_number ==_split_occurence.size())
      _split_occurence.emplace_back(bitVector(_max_bs_trees));
//        _split_occurence.emplace_back(bitVector());

    _split_occurence[e->bip_number][_num_bs_trees] = true;
//    _split_occurence[e->bip_number].set(_num_bs_trees);
  }

  pllmod_utree_split_destroy(splits);

  assert(_split_occurence.size() == _pll_splits_hash->entry_count);

  _num_bs_trees++;
}

splitEntryVector BootstopCheck::all_splits()
{
  splitEntryVector all_splits;

  /* collect all splits from the hashtable into array */
  for (size_t i = 0; i < _pll_splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  _pll_splits_hash->table[i];
    while (e != NULL)
    {
      assert(e->bip_number < _pll_splits_hash->entry_count);

      all_splits.push_back(e);

      e = e->next;
    }
  }

  assert(all_splits.size() == _pll_splits_hash->entry_count);

  return all_splits;
}

bool BootstopCheck::converged(unsigned long random_seed)
{
  RandomGenerator gen(random_seed);

  if (!_num_bs_trees)
    return false;

  assert(_pll_splits_hash);

  return check_convergence(gen);
}

BootstopCheckMRE::BootstopCheckMRE(size_t max_bs_trees, double cutoff,
                                   size_t num_permutations) : BootstopCheck(max_bs_trees),
                                       _wrf_cutoff(cutoff), _num_permutations(num_permutations),
                                       _avg_wrf(0.), _avg_pct(0.), _num_better(0)
{
}

BootstopCheckMRE::~BootstopCheckMRE ()
{
}

bool BootstopCheckMRE::check_convergence(RandomGenerator& gen)
{
  bool converged = false;
  const auto num_splits = _pll_splits_hash->entry_count;
  uintVector perm(_num_bs_trees);
  uintVector support1(num_splits), support2(num_splits);
  splitEntryVector cons1_splits, cons2_splits;

  size_t min_better_count = 0.99 * _num_permutations;
  double wrf_thresh_avg = 0;
  _num_better = 0;
  _avg_pct = 0;
  _avg_wrf = 0;

  auto splits_all = all_splits();

  /* init permutation array with 1:1 mapping */
  for (size_t i = 0; i < _num_bs_trees; ++i)
    perm[i] = i;

  for (size_t p = 0; p < _num_permutations; ++p)
  {
    /* shuffle tree indices to divide trees into 2 random subsets */
    std::shuffle(perm.begin(), perm.end(), gen);

    /* iterate over all splits in the hashtable */
    for (const auto e: splits_all)
    {
      /* for each split, compute how many times it occurred in both tree subsets */
      unsigned int cnt1 = 0;
      unsigned int cnt2 = 0;
      const auto& occ = _split_occurence[e->bip_number];
      for(size_t j = 0; j < _num_bs_trees; j++)
      {
        if (occ[j])
        {
          if(perm[j] % 2 == 0)
            cnt1++;
          else
            cnt2++;
        }
      }

      support1[e->bip_number] = cnt1;
      support2[e->bip_number] = cnt2;
    }

    /* build MRE consensus trees for both subsets */
    mre(splits_all, support1, cons1_splits);
    mre(splits_all, support2, cons2_splits);

    /* compute weighted RF distance between consensus trees from splits */
    double wrf = consensus_wrf_distance(cons1_splits, cons2_splits, support1, support2);

    auto half_split_count = 0.5 * _num_bs_trees * (cons1_splits.size() + cons2_splits.size());

    /*
       wrf_thresh is the 'custom' threshold computed for this pair
       of majority rules trees (i.e. one of the BS_PERMS splits),
       and simply takes into account the resolution of the two trees
    */
    auto wrf_thresh = _wrf_cutoff * half_split_count;

    /*
      we count this random split as 'succeeding' when
       the wrf between maj rules trees is exceeded
       by its custom threshold
    */
    if (wrf <= wrf_thresh)
      _num_better++;

    /*
       here we accumulate outcomes and thresholds, because
       we're not going to stop until the avg dist is less
       than the avg threshold
    */
    _avg_pct += wrf / half_split_count  * 100.0;
    _avg_wrf += wrf;
    wrf_thresh_avg += wrf_thresh;

  } // permutations

  _avg_pct /= (double) _num_permutations;
  _avg_wrf /= (double) _num_permutations;
  wrf_thresh_avg /= (double) _num_permutations;

  converged = (_num_better >= min_better_count && _avg_wrf <= wrf_thresh_avg);

  return converged;
}

void BootstopCheckMRE::mre(splitEntryVector& splits_all, const uintVector& support,
                           splitEntryVector& splits_cons)
{
  auto mr_support_cuttoff   = _num_bs_trees / 4;
  auto split_len            = _pll_splits_hash->bitv_len;
  auto tip_count            = _pll_splits_hash->bit_count;
  auto max_splits           =  tip_count - 3;

  /* sort all splits by their support in descending order */
  std::sort(splits_all.begin(), splits_all.end(),
            [&support](bitv_hash_entry_t * e1, bitv_hash_entry_t *e2)
               { return support[e1->bip_number] > support[e2->bip_number]; }
  );

  splits_cons.clear();
  splits_cons.reserve(max_splits);
  for (auto e: splits_all)
  {
    bool compatible = true;

    if (support[e->bip_number] <= mr_support_cuttoff)
    {
      for (auto ce = splits_cons.rbegin(); ce != splits_cons.rend(); ce++)
      {
        if (!pllmod_utree_compatible_splits((*ce)->bit_vector, e->bit_vector,
                                            split_len, tip_count))
        {
          compatible = false;
          break;
        }
      }
    }

    if (compatible)
      splits_cons.push_back(e);

//      printf("add split: %d   %u   %u %08x   ->   %s\n",
//             0, e->bip_number, support[e->bip_number], e->bit_vector[0],
//             compatible ? "YES" : "NO");

          /* we already have a fully-resolved tree -> exit */
    if (splits_cons.size() == max_splits)
      break;
  }

  assert(splits_cons.size() <= max_splits);

  /* sort splits by bip_number */
  std::sort(splits_cons.begin(), splits_cons.end(),
            [](bitv_hash_entry_t * e1, bitv_hash_entry_t *e2)
               { return e1->bip_number < e2->bip_number; }
  );
}

double BootstopCheckMRE::consensus_wrf_distance(const splitEntryVector& splits1,
                                                const splitEntryVector& splits2,
                                                const uintVector& support1,
                                                const uintVector& support2)
{
  double wrf = 0;
  auto e1 = splits1.cbegin();
  auto e2 = splits2.cbegin();
  while (e1 != splits1.cend() || e2 != splits2.cend())
  {
    if (e2 == splits2.cend() || (e1 != splits1.cend() && (*e1)->bip_number < (*e2)->bip_number))
    {
      wrf += support1[(*e1)->bip_number];
      e1++;
    }
    else
    {
      if (e1 == splits1.cend() || (e2 < splits2.cend() && (*e2)->bip_number < (*e1)->bip_number) )
      {
        wrf += support2[(*e2)->bip_number];
        e2++;
      }
      else
      {
        assert ((*e1)->bip_number == (*e2)->bip_number);

        auto cnt1 = support1[(*e1)->bip_number];
        auto cnt2 = support2[(*e2)->bip_number];

        wrf += ((cnt1 > cnt2) ? cnt1 - cnt2 : cnt2 - cnt1);

        e1++;
        e2++;
      }
    }
  }

  return wrf;
}
