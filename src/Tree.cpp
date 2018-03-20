#include <algorithm>

#include "Tree.hpp"

using namespace std;

Tree::Tree (const Tree& other) : BasicTree(other._num_tips),
    _pll_utree(other.pll_utree_copy())
{
}

Tree::Tree (Tree&& other) : BasicTree(other._num_tips), _pll_utree(other._pll_utree.release())
{
  other._num_tips = 0;
  swap(_pll_utree_tips, other._pll_utree_tips);
}

Tree& Tree::operator=(const Tree& other)
{
  if (this != &other)
  {
    _pll_utree.reset(other.pll_utree_copy());
    _num_tips = other._num_tips;
    _pll_utree_tips.clear();
  }

  return *this;
}

Tree& Tree::operator=(Tree&& other)
{
  if (this != &other)
  {
    _num_tips = 0;
    _pll_utree_tips.clear();
    _pll_utree.release();

    swap(_num_tips, other._num_tips);
    swap(_pll_utree, other._pll_utree);
    swap(_pll_utree_tips, other._pll_utree_tips);
  }

  return *this;
}

Tree::~Tree ()
{
}

Tree Tree::buildRandom(size_t num_tips, const char * const* tip_labels)
{
  PllUTreeUniquePtr pll_utree(pllmod_utree_create_random(num_tips, tip_labels));

  libpll_check_error("ERROR building random tree");
  assert(pll_utree);

  return Tree(pll_utree);
}

Tree Tree::buildRandom(const NameList& taxon_names)
{
  std::vector<const char*> tip_labels(taxon_names.size(), nullptr);
  for (size_t i = 0; i < taxon_names.size(); ++i)
    tip_labels[i] = taxon_names[i].data();

  return Tree::buildRandom(taxon_names.size(), (const char * const*) tip_labels.data());
}

Tree Tree::buildParsimony(const PartitionedMSA& parted_msa, unsigned int random_seed,
                           unsigned int attributes, unsigned int * score)
{
  unsigned int lscore;
  unsigned int *pscore = score ? score : &lscore;

  LOG_DEBUG << "Parsimony seed: " << random_seed << endl;

  auto taxon_names = parted_msa.taxon_names();
  auto taxon_count = taxon_names.size();
  std::vector<const char*> tip_labels(taxon_names.size(), nullptr);
  for (size_t i = 0; i < taxon_names.size(); ++i)
    tip_labels[i] = taxon_names[i].data();

  // create pll_partitions
  std::vector<pll_partition*> pars_partitions(parted_msa.part_count(), nullptr);
  size_t i = 0;
  for (const auto& pinfo: parted_msa.part_list())
  {
    const auto& model = pinfo.model();
    const auto& msa = pinfo.msa();

    auto partition = pll_partition_create(taxon_count,
                                         0,   /* number of CLVs */
                                         model.num_states(),
                                         msa.length(),
                                         1,
                                         1, /* pmatrix count */
                                         1,  /* rate_cats */
                                         0,  /* scale buffers */
                                         attributes);

    /* set pattern weights */
    if (!msa.weights().empty())
      pll_set_pattern_weights(partition, msa.weights().data());

    /* set tip states */
    for (size_t j = 0; j < msa.size(); ++j)
    {
      pll_set_tip_states(partition, j, model.charmap(), msa.at(j).c_str());
    }

    pars_partitions[i++] = partition;
  }
  assert(i == pars_partitions.size());

  PllUTreeUniquePtr pll_utree(pllmod_utree_create_parsimony_multipart(taxon_count,
                                                                      (char* const*) tip_labels.data(),
                                                                      pars_partitions.size(),
                                                                      pars_partitions.data(),
                                                                      random_seed,
                                                                      pscore));

  for (auto p: pars_partitions)
    pll_partition_destroy(p);

  libpll_check_error("ERROR building parsimony tree");
  assert(pll_utree);

  return Tree(pll_utree);
}

Tree Tree::loadFromFile(const std::string& file_name)
{
  pll_utree_t * utree;
  pll_rtree_t * rtree;
  const char* fname = file_name.c_str();

  if (!(rtree = pll_rtree_parse_newick(fname)))
  {
    utree = pll_utree_parse_newick(fname);
    if (!utree)
    {
      libpll_check_error("ERROR reading tree file");
    }
  }
  else
  {
//    LOG_INFO << "NOTE: You provided a rooted tree; it will be automatically unrooted." << endl;
    utree = pll_rtree_unroot(rtree);

    /* optional step if using default PLL clv/pmatrix index assignments */
    pll_utree_reset_template_indices(get_pll_utree_root(utree), utree->tip_count);

    libpll_check_error("ERROR unrooting the tree");
  }

  assert(utree);

  return Tree(PllUTreeUniquePtr(utree));
}

PllNodeVector const& Tree::tip_nodes() const
{
 if (_pll_utree_tips.empty() && _num_tips > 0)
 {
   assert(_num_tips == _pll_utree->tip_count);

   _pll_utree_tips.assign(_pll_utree->nodes, _pll_utree->nodes + _pll_utree->tip_count);
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

NameIdMap Tree::tip_ids() const
{
  NameIdMap result;
  for (auto const& node: tip_nodes())
    result.emplace(string(node->label), node->clv_index);

  assert(!result.empty());

  return result;
}


void Tree::reset_tip_ids(const NameIdMap& label_id_map)
{
  if (label_id_map.size() != _num_tips)
    throw invalid_argument("Invalid map size");

  for (auto& node: tip_nodes())
  {
    const unsigned int tip_id = label_id_map.at(node->label);
    node->clv_index = node->node_index = tip_id;
  }
}


void Tree::fix_missing_brlens(double new_brlen)
{
  pllmod_utree_set_length_recursive(_pll_utree.get(), new_brlen, 1);
}

void Tree::reset_brlens(double new_brlen)
{
  pllmod_utree_set_length_recursive(_pll_utree.get(), new_brlen, 0);
}

PllNodeVector Tree::subnodes() const
{
  PllNodeVector subnodes;

  if (_num_tips > 0)
  {
    subnodes.resize(num_subnodes());

    for (size_t i = 0; i < _pll_utree->tip_count + _pll_utree->inner_count; ++i)
    {
      auto node = _pll_utree->nodes[i];
      subnodes[node->node_index] = node;
      if (node->next)
      {
        subnodes[node->next->node_index] = node->next;
        subnodes[node->next->next->node_index] = node->next->next;
      }
    }
  }

  return subnodes;
}

TreeTopology Tree::topology() const
{
  TreeTopology topol;

  for (auto n: subnodes())
  {
    if (n->node_index < n->back->node_index)
      topol.emplace_back(n->node_index, n->back->node_index, n->length);
  }

//  for (auto& branch: topol)
//    printf("%u %u %lf\n", branch.left_node_id, branch.right_node_id, branch.length);

  assert(topol.size() == num_branches());

  return topol;
}

void Tree::topology(const TreeTopology& topol)
{
  if (topol.size() != num_branches())
    throw runtime_error("Incompatible topology!");

  auto allnodes = subnodes();
  unsigned int pmatrix_index = 0;
  for (const auto& branch: topol)
  {
    pll_unode_t * left_node = allnodes.at(branch.left_node_id);
    pll_unode_t * right_node = allnodes.at(branch.right_node_id);
    pllmod_utree_connect_nodes(left_node, right_node, branch.length);

    // important: make sure all branches have distinct pmatrix indices!
    left_node->pmatrix_index = right_node->pmatrix_index = pmatrix_index++;
//    printf("%u %u %lf %d\n", branch.left_node_id, branch.right_node_id, branch.length, left_node->pmatrix_index);
  }

  assert(pmatrix_index == num_branches());
}

TreeCollection::const_iterator TreeCollection::best() const
{
  return std::max_element(_trees.cbegin(), _trees.cend(),
                          [](const value_type& a, const value_type& b) -> bool
                          { return a.first < b.first; }
                         );
}

void TreeCollection::push_back(double score, const Tree& tree)
{
  _trees.emplace_back(score, tree.topology());
}

void TreeCollection::push_back(double score, TreeTopology&& topol)
{
  _trees.emplace_back(score, topol);
}

pll_unode_t* get_pll_utree_root(const pll_utree_t* tree)
{
  return tree->nodes[tree->tip_count + tree->inner_count - 1];
}
