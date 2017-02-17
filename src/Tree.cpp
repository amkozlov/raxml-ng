/*
 * Tree.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: alex
 */

#include "Tree.hpp"

using namespace std;

Tree& Tree::operator=(Tree&& other)
{
  if (this != &other)
  {
    _num_tips = 0;
    _pll_utree_tips.clear();
    if (_pll_utree_start)
    {
      pll_utree_destroy(_pll_utree_start, nullptr);
     _pll_utree_start = nullptr;
    }

    swap(_num_tips, other._num_tips);
    swap(_pll_utree_start, other._pll_utree_start);
    swap(_pll_utree_tips, other._pll_utree_tips);
  }

  return *this;
}

Tree::~Tree ()
{
  if (_pll_utree_start)
    pll_utree_destroy(_pll_utree_start, nullptr);
}

Tree Tree::buildRandom(size_t num_tips, const char * const* tip_labels)
{
  Tree tree;

  tree._num_tips = num_tips;
  tree._pll_utree_start = pllmod_utree_create_random(num_tips, tip_labels);

  return tree;
}

Tree Tree::buildParsimony(const PartitionedMSA& parted_msa, unsigned int random_seed,
                           unsigned int attributes, unsigned int * score)
{
  Tree tree;
  unsigned int lscore;
  unsigned int *pscore = score ? score : &lscore;

  const MSA& msa = parted_msa.full_msa();

  // temporary workaround
  unsigned int num_states = parted_msa.model(0).num_states();
  const unsigned int * map = parted_msa.model(0).charmap();
  const unsigned int * weights = msa.weights().empty() ? nullptr : msa.weights().data();

  tree._num_tips = msa.size();


  tree._pll_utree_start = pllmod_utree_create_parsimony(msa.size(),
                                                        msa.length(),
                                                        msa.pll_msa()->label,
                                                        msa.pll_msa()->sequence,
                                                        weights,
                                                        map,
                                                        num_states,
                                                        attributes,
                                                        random_seed,
                                                        pscore);

  if (!tree._pll_utree_start)
    throw runtime_error("ERROR building parsimony tree: " + string(pll_errmsg));

  return tree;
}

Tree Tree::loadFromFile(const std::string& file_name)
{
  Tree tree;

  pll_utree_t * utree;
  pll_rtree_t * rtree;

  unsigned int tip_count;
  if (!(rtree = pll_rtree_parse_newick(file_name.c_str(), &tip_count)))
  {
    if (!(utree = pll_utree_parse_newick(file_name.c_str(), &tip_count)))
    {
      throw runtime_error("ERROR reading tree file: " + string(pll_errmsg));
    }
  }
  else
  {
//    LOG_INFO << "NOTE: You provided a rooted tree; it will be automatically unrooted." << endl;
    utree = pll_rtree_unroot(rtree);

    /* optional step if using default PLL clv/pmatrix index assignments */
    pll_utree_reset_template_indices(utree, tip_count);
  }

  tree._num_tips = tip_count;
  tree._pll_utree_start = utree;

  return tree;
}

std::vector<pll_utree_t*> const& Tree::tip_nodes() const
{
 if (_pll_utree_tips.empty() && _num_tips > 0)
 {
   _pll_utree_tips.resize(_num_tips);

   pll_utree_query_tipnodes(_pll_utree_start, _pll_utree_tips.data());
 }

 return _pll_utree_tips;
}

IdNameVector Tree::tip_labels() const
{
  IdNameVector result;
  for (auto const& node: tip_nodes())
    result.emplace_back(node->clv_index, string(node->label));

  assert(!result.empty());

  return result;
}

void Tree::reset_tip_ids(const NameIdMap& label_id_map)
{
  if (label_id_map.size() != _num_tips)
    throw invalid_argument("Invalid map size");

  tip_nodes();
  for (auto& node: _pll_utree_tips)
  {
    const unsigned int tip_id = label_id_map.at(node->label);
    node->clv_index = node->node_index = tip_id;
  }
}


void Tree::fix_missing_brlens(double new_brlen)
{
  pllmod_utree_set_length_recursive(_pll_utree_start, new_brlen, 1);
}

