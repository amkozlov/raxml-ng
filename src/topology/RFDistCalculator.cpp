#include "RFDistCalculator.hpp"

using namespace std;

RFDistCalculator::RFDistCalculator (const TreeList& trees, bool lowmem) :
    _num_trees(0), _num_tips(0), _avg_rf(0.0), _avg_rrf(0.0), _num_uniq_trees(0)
{
  if (trees.size() > 1)
  {
    _num_trees = trees.size();
    _num_tips = trees.at(0).num_tips();
    if (lowmem)
      calc_rfdist_lowmem(trees);
    else
      calc_rfdist(trees);
  }
  else
    throw runtime_error("Need at least 2 trees to compute RF distances! "
                        "Given: " + to_string(trees.size()));
}

RFDistCalculator::~RFDistCalculator ()
{
}

void RFDistCalculator::add_tree_splits(size_t tree_idx, const Tree& tree,
                                       bitv_hashtable_t * splits_hash)
{
  assert(splits_hash);
  assert(tree.num_tips() == _num_tips);
  assert(tree_idx < _num_trees);

  pll_split_t * splits = pllmod_utree_split_create(&tree.pll_utree_root(),
                                                 tree.num_tips(),
                                                 nullptr);

  for (size_t i = 0; i < tree.num_splits(); ++i)
  {
    bitv_hash_entry_t * e = pllmod_utree_split_hashtable_insert_single(splits_hash,
                                                                       splits[i],
                                                                       1.0);
    if (!e)
      libpll_check_error("Cannot add a split into hashtable: ", true);

    assert(e->bip_number <= _split_occurence.size());

    /* new split -> create bit vector with tree occurrence flags */
    if (e->bip_number ==_split_occurence.size())
      _split_occurence.emplace_back(bitVector(_num_trees));

    _split_occurence[e->bip_number][tree_idx] = true;
  }

  pllmod_utree_split_destroy(splits);
}

void RFDistCalculator::calc_rfdist(const TreeList& trees)
{
  bitv_hashtable_t * splits_hash = pllmod_utree_split_hashtable_create(_num_tips, 0);

  if (!splits_hash)
  {
    assert(pll_errno);
    libpll_check_error("Cannot create split hashtable");
  }

  /* add splits from all trees into a hashtable */
  for (size_t i = 0; i < _num_trees; ++i)
  {
    add_tree_splits(i, trees.at(i), splits_hash);
  }

  assert(_split_occurence.size() == splits_hash->entry_count);

  /* now compute all pairwise RF distances using hashtable */
  _rfdist_mat.resize(_num_trees * _num_trees, 0.);

  /* iterate over all splits in the hashtable */
  for (size_t i = 0; i < splits_hash->table_size; ++i)
  {
    bitv_hash_entry_t * e =  splits_hash->table[i];
    while (e != NULL)
    {
      assert(e->bip_number < splits_hash->entry_count);

      const auto& occ = _split_occurence[e->bip_number];
      for(size_t j = 0; j < _num_trees; j++)
      {
        if (occ[j])
        {
          for(size_t k = 0; k < _num_trees; k++)
          {
            if (j == k)
              continue;

            if (!occ[k])
            {
              _rfdist_mat[j * _num_trees + k]++;
            }
          }
        }
      }
      e = e->next;
    }
  }

  pllmod_utree_split_hashtable_destroy(splits_hash);

  /* compute averages */
  _avg_rf = std::accumulate(_rfdist_mat.begin(), _rfdist_mat.end(), 0);
  _num_uniq_trees = 1;
  for(size_t j = 0; j < _num_trees-1; j++)
  {
    bool uniq = true;
    for(size_t k = j+1; k < _num_trees; k++)
    {
      auto rf = _rfdist_mat[j * _num_trees + k] + _rfdist_mat[k * _num_trees + j];
      _rfdist_mat[j * _num_trees + k] = _rfdist_mat[k * _num_trees + j] = rf;
      uniq &= (rf > 0);
    }

    if (uniq)
      _num_uniq_trees++;
  }

  auto num_pairs = _num_trees * (_num_trees - 1) / 2;
  _avg_rf /= num_pairs;
  _avg_rrf = _avg_rf / maxrf();
}

void RFDistCalculator::calc_rfdist_lowmem(const TreeList& trees)
{
  assert(trees.size() > 0);

  /* extract splits from all trees */
  std::vector<pll_split_t *> splits(_num_trees);
  for (size_t i = 0; i < _num_trees; ++i)
  {
    const auto& tree = trees.at(i);
    splits[i] = pllmod_utree_split_create(&tree.pll_utree_root(),
                                          tree.num_tips(),
                                          nullptr);
  }

  _avg_rf = 0.0;
  _avg_rrf = 0.0;
  _num_uniq_trees = 1;
  size_t num_pairs = 0;

  for (size_t i = 0; i < _num_trees-1; ++i)
  {
    bool uniq = true;
    for (size_t j = i+1; j < _num_trees; ++j)
    {
      auto rf = pllmod_utree_split_rf_distance(splits[i], splits[j], _num_tips);
      _avg_rf += rf;

      // TODO: maxrf will be different for multifurcating trees
      double rrf = ((double) rf) / maxrf();
      _avg_rrf += rrf;

      uniq &= (rf > 0);
      num_pairs++;
    }

    if (uniq)
      _num_uniq_trees++;
  }

  for (auto s: splits)
    pllmod_utree_split_destroy(s);

  _avg_rf /= num_pairs;
  _avg_rrf /= num_pairs;
}

double RFDistCalculator::avg_rf() const
{
  return _avg_rf;
}

double RFDistCalculator::avg_rrf() const
{
  return _avg_rrf;
}

size_t RFDistCalculator::num_uniq_trees() const
{
  return _num_uniq_trees;
}

double RFDistCalculator::maxrf() const
{
  return (double) 2 * (_num_tips - 3);
}

size_t RFDistCalculator::num_trees() const
{
  return _num_trees;
}

size_t RFDistCalculator::num_tips() const
{
  return _num_tips;
}

size_t RFDistCalculator::rf(size_t i, size_t j) const
{
  return _rfdist_mat.empty() ? 0 :_rfdist_mat[i * _num_trees + j];
}

double RFDistCalculator::rrf(size_t i, size_t j) const
{
 // TODO: maxrf will be different for multifurcating trees
 return rf(i, j) / maxrf();
}

std::fstream& operator<<(std::fstream& stream, const RFDistCalculator& rfcalc)
{
  auto num_trees = rfcalc.num_trees();
  const string delim = "\t";
  if (num_trees > 0)
  {
    stream << fixed;
    for (size_t i = 0; i < num_trees-1; ++i)
    {
      for (size_t j = i+1; j < num_trees; ++j)
      {
        stream << i << delim << j << delim
               << rfcalc.rf(i, j) << delim << FMT_BL(rfcalc.rrf(i, j)) << endl;
      }
    }
  }
  return stream;
}

