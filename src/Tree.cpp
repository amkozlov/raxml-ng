#include <algorithm>

#include "Tree.hpp"
#include "io/file_io.hpp"

using namespace std;

Tree::Tree (const Tree& other) : BasicTree(other._num_tips),
    _pll_utree(other.pll_utree_copy()), _partition_brlens(other._partition_brlens)
{
}

Tree::Tree (Tree&& other) : BasicTree(other._num_tips), _pll_utree(other._pll_utree.release())
{
  other._num_tips = 0;
  swap(_pll_utree_tips, other._pll_utree_tips);
  swap(_partition_brlens, other._partition_brlens);
}

Tree& Tree::operator=(const Tree& other)
{
  if (this != &other)
  {
    _pll_utree.reset(other.pll_utree_copy());
    _num_tips = other._num_tips;
    _pll_utree_tips.clear();
    _partition_brlens = other._partition_brlens;
  }

  return *this;
}

Tree& Tree::operator=(Tree&& other)
{
  if (this != &other)
  {
    _num_tips = 0;
    _pll_utree_tips.clear();
    _partition_brlens.clear();

    _pll_utree.reset(other._pll_utree.release());

    swap(_num_tips, other._num_tips);
    swap(_pll_utree_tips, other._pll_utree_tips);
    swap(_partition_brlens, other._partition_brlens);
  }

  return *this;
}

Tree::~Tree ()
{
}

size_t Tree::num_inner() const
{
  return _pll_utree ? _pll_utree->inner_count : BasicTree::num_inner();
}

size_t Tree::num_branches() const
{
  return _pll_utree ? _pll_utree->edge_count : BasicTree::num_branches();
}

bool Tree::binary() const
{
  return _pll_utree ? _pll_utree->binary : BasicTree::binary();
}

pll_utree_t * Tree::pll_utree_copy() const
{
  return _pll_utree ? pll_utree_clone(_pll_utree.get()) : nullptr;
}

void Tree::pll_utree(const pll_utree_t& tree)
{
  _num_tips = tree.tip_count;
  _pll_utree.reset(pll_utree_clone(&tree));
  _pll_utree_tips.clear();
}

void Tree::pll_utree(unsigned int tip_count, const pll_unode_t& root)
{
  _num_tips = tip_count;
  _pll_utree.reset(pll_utree_wraptree_multi(pll_utree_graph_clone(&root), _num_tips, 0));
  _pll_utree_tips.clear();
}

Tree Tree::buildRandom(size_t num_tips, const char * const* tip_labels,
                       unsigned int random_seed)
{
  PllUTreeUniquePtr pll_utree(pllmod_utree_create_random(num_tips, tip_labels, random_seed));

  libpll_check_error("ERROR building random tree");
  assert(pll_utree);

  return Tree(pll_utree);
}

Tree Tree::buildRandom(const NameList& taxon_names, unsigned int random_seed)
{
  std::vector<const char*> tip_labels(taxon_names.size(), nullptr);
  for (size_t i = 0; i < taxon_names.size(); ++i)
    tip_labels[i] = taxon_names[i].data();

  return Tree::buildRandom(taxon_names.size(), (const char * const*) tip_labels.data(),
                           random_seed);
}

Tree Tree::buildRandomConstrained(const NameList& taxon_names, unsigned int random_seed,
                                  const Tree& constrained_tree)
{
  PllUTreeUniquePtr pll_utree(pllmod_utree_resolve_multi(&constrained_tree.pll_utree(),
                                                         random_seed, nullptr));

  if (!pll_utree)
  {
    assert(pll_errno);
    libpll_check_error("ERROR in building a randomized constrained tree");
  }

  Tree tree(pll_utree);

  if (taxon_names.size() > tree.num_tips())
  {
    // constraint tree is not comprehensive -> add free taxa
    auto free_tip_count = taxon_names.size() - tree.num_tips();
    auto cons_tips = tree.tip_ids();
    NameList free_tips;
    free_tips.reserve(free_tip_count);

    for (const auto& t: taxon_names)
    {
      if (!cons_tips.count(t))
        free_tips.push_back(t);
    }

    assert(free_tips.size() == free_tip_count);

    tree.insert_tips_random(free_tips, random_seed);
  }

//  pll_utree_check_integrity(&tree.pll_utree());

  return tree;
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
  Tree tree;
  NewickStream ns(file_name, std::ios::in);

  ns >> tree;

  return tree;
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

std::vector<const char*> Tree::tip_labels_cstr() const
{
  std::vector<const char*> result;

  if (!empty())
  {
    result.resize(_num_tips, nullptr);
    for (auto const& node: tip_nodes())
      result[node->clv_index] =  node->label;
  }

  return result;
}

NameList Tree::tip_labels_list() const
{
  NameList result;

  if (!empty())
  {
    result.resize(_num_tips);
    for (auto const& node: tip_nodes())
      result[node->clv_index] =  string(node->label);
  }

  return result;
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

void Tree::insert_tips_random(const NameList& tip_names, unsigned int random_seed)
{
  _pll_utree_tips.clear();

  std::vector<const char*> tip_labels(tip_names.size(), nullptr);
  for (size_t i = 0; i < tip_names.size(); ++i)
    tip_labels[i] = tip_names[i].data();

  int retval = pllmod_utree_extend_random(_pll_utree.get(),
                                          tip_labels.size(),
                                          (const char * const*) tip_labels.data(),
                                          random_seed);

  if (retval)
    _num_tips = _pll_utree->tip_count;
  else
  {
    assert(pll_errno);
    libpll_check_error("ERROR in randomized tree extension");
  }
}

void Tree::reset_tip_ids(const NameIdMap& label_id_map)
{
  if (label_id_map.size() < _num_tips)
    throw invalid_argument("Invalid map size");

  for (auto& node: tip_nodes())
  {
    const unsigned int tip_id = label_id_map.at(node->label);
    node->clv_index = node->node_index = tip_id;
  }
}

void Tree::fix_outbound_brlens(double min_brlen, double max_brlen)
{
  for (auto n: subnodes())
  {
    n->length = std::max(min_brlen, std::min(n->length, max_brlen));
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

void Tree::collapse_short_branches(double min_brlen)
{
  if (!pllmod_utree_collapse_branches(_pll_utree.get(), min_brlen))
    libpll_check_error("Failed to collapse short branches: ", true);
}

PllNodeVector Tree::subnodes() const
{
  PllNodeVector subnodes;

  if (_num_tips > 0)
  {
    subnodes.resize(num_subnodes());

    for (size_t i = 0; i < _pll_utree->tip_count + _pll_utree->inner_count; ++i)
    {
      auto start = _pll_utree->nodes[i];
      auto node = start;
      do
      {
        subnodes[node->node_index] = node;
        node = node->next;
      }
      while (node && node != start);
    }
  }

  return subnodes;
}

TreeTopology Tree::topology() const
{
  TreeTopology topol;

  /* empty tree -> return empty topology */
  if (!num_tips())
    return topol;

  topol.vroot_node_id = _pll_utree->vroot->node_index;

  topol.edges.resize(num_branches());

  size_t branches = 0;
  for (auto n: subnodes())
  {
    assert(n);
    if (n->node_index < n->back->node_index)
    {
      topol.edges.at(n->pmatrix_index) = TreeBranch(n->node_index, n->back->node_index, n->length);
      branches++;
    }
  }
  topol.brlens = _partition_brlens;

//  for (auto& branch: topol.edges)
//    printf("%u %u %lf\n", branch.left_node_id, branch.right_node_id, branch.length);

  assert(branches == num_branches());

  return topol;
}

void Tree::topology(const TreeTopology& topol)
{
  if (topol.edges.size() != num_branches())
    throw runtime_error("Incompatible topology!");

  auto allnodes = subnodes();
  unsigned int pmatrix_index = 0;
  for (const auto& branch: topol)
  {
    pll_unode_t * left_node = allnodes.at(branch.left_node_id);
    pll_unode_t * right_node = allnodes.at(branch.right_node_id);
    pllmod_utree_connect_nodes(left_node, right_node, branch.length);

    // important: make sure all branches have distinct pmatrix indices!
    left_node->pmatrix_index = right_node->pmatrix_index = pmatrix_index;

    pmatrix_index++;
//    printf("%u %u %lf %d  (%u - %u) \n", branch.left_node_id, branch.right_node_id,
//           branch.length, left_node->pmatrix_index, left_node->clv_index, right_node->clv_index);
  }

  _pll_utree->vroot = allnodes[topol.vroot_node_id];

  _partition_brlens = topol.brlens;

  assert(pmatrix_index == num_branches());
}

const doubleVector& Tree::partition_brlens(size_t partition_idx) const
{
  return _partition_brlens.at(partition_idx);
}

void Tree::partition_brlens(size_t partition_idx, const doubleVector& brlens)
{
  _partition_brlens.at(partition_idx) = brlens;
}

void Tree::partition_brlens(size_t partition_idx, doubleVector&& brlens)
{
  _partition_brlens.at(partition_idx) = brlens;
}

void Tree::add_partition_brlens(doubleVector&& brlens)
{
  _partition_brlens.push_back(brlens);
}

void Tree::apply_partition_brlens(size_t partition_idx)
{
  if (partition_idx >= _partition_brlens.size())
    throw out_of_range("Partition ID out of range");

  const auto brlens = _partition_brlens.at(partition_idx);
  for (auto n: subnodes())
  {
    n->length = brlens[n->pmatrix_index];
  }
}

void Tree::apply_avg_brlens(const doubleVector& partition_contributions)
{
  assert(!_partition_brlens.empty() && partition_contributions.size() == _partition_brlens.size());

  const auto allnodes = subnodes();

  for (auto n: allnodes)
    n->length = 0;

  for (size_t p = 0; p < _partition_brlens.size(); ++p)
  {
    const auto brlens = _partition_brlens[p];
    const auto w = partition_contributions[p];
    for (auto n: allnodes)
      n->length += brlens[n->pmatrix_index] * w;
  }
}

void Tree::reroot(const NameList& outgroup_taxa, bool add_root_node)
{
  // collect tip node indices
  NameIdMap name_id_map;
  for (auto const& node: tip_nodes())
    name_id_map.emplace(string(node->label), node->node_index);

  // find tip ids for outgroup taxa
  uintVector tip_ids;
  for (const auto& label: outgroup_taxa)
  {
    const auto tip_id = name_id_map.at(label);
    tip_ids.push_back(tip_id);
  }

  // re-root tree with the outgroup
  int res = pllmod_utree_outgroup_root(_pll_utree.get(), tip_ids.data(), tip_ids.size(),
                                       add_root_node);

  if (!res)
    libpll_check_error("Unable to reroot tree");
}

ScoredTopologyMap::const_iterator ScoredTopologyMap::best() const
{
  return std::max_element(_trees.cbegin(), _trees.cend(),
                          [](const value_type& a, const value_type& b) -> bool
                          { return a.second.first < b.second.first; }
                         );
}

const ScoredTopologyMap::mapped_type& ScoredTopologyMap::at(size_t index) const
{
  if (_trees.count(index))
    return _trees.at(index);
  else
    throw runtime_error("ScoredTopologyMap: Invalid tree id: " + to_string(index));
}

