#ifndef RAXML_TREE_HPP_
#define RAXML_TREE_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"

// seems to be the only way to have custom deleter for unique_ptr
// without having to specify it every time during object creation
namespace std
{
  template<>
  struct default_delete<pll_utree_t> {
    void operator()(pll_utree_t* ptr) { pll_utree_destroy(ptr, nullptr); }
  };
}

struct TreeBranch
{
  TreeBranch() : left_node_id(0), right_node_id(0), length(0.) {};
  TreeBranch(size_t left_node_id, size_t right_node_id, double length) :
    left_node_id(left_node_id), right_node_id(right_node_id), length(length) {};

  size_t left_node_id;
  size_t right_node_id;
  double length;
};

struct TreeTopology
{
  typedef std::vector<TreeBranch> edge_container;
  typedef typename edge_container::iterator        iterator;
  typedef typename edge_container::const_iterator  const_iterator;

  //Iterator Compatibility
  iterator begin() { return edges.begin(); }
  iterator end() { return edges.end(); }
  const_iterator begin() const { return edges.cbegin(); }
  const_iterator end() const { return edges.cend(); }
  const_iterator cbegin() { return edges.cbegin(); }
  const_iterator cend() { return edges.cend(); }

  size_t vroot_node_id;
  edge_container edges;
  std::vector<doubleVector> brlens;
};

typedef std::unique_ptr<pll_utree_t> PllUTreeUniquePtr;
typedef std::vector<pll_unode_t*> PllNodeVector;

class BasicTree
{
public:
  BasicTree(size_t num_tips) : _num_tips(num_tips) {}
  virtual ~BasicTree() {}

  bool empty() const { return _num_tips == 0; };
  virtual bool binary() const { return true; };
  virtual size_t num_tips() const { return _num_tips; };
  virtual size_t num_inner() const { return _num_tips - 2; };
  virtual size_t num_nodes() const { return num_tips() + num_inner(); };
  virtual size_t num_subnodes() const { return num_branches() * 2; };
  virtual size_t num_branches() const { return _num_tips ? _num_tips + _num_tips - 3 : 0; };
  virtual size_t num_splits() const { return num_branches() - _num_tips; };

protected:
  size_t _num_tips;
};

class Tree : public BasicTree
{
public:
  Tree() : BasicTree(0), _pll_utree(nullptr) {}
  Tree(unsigned int tip_count, const pll_unode_t& root) :
    BasicTree(tip_count),
    _pll_utree(pll_utree_wraptree(pll_utree_graph_clone(&root), tip_count)) {}
  Tree(const pll_utree_t& pll_utree) :
    BasicTree(pll_utree.tip_count), _pll_utree(pll_utree_clone(&pll_utree)) {}
  Tree(std::unique_ptr<pll_utree_t>&  pll_utree) :
    BasicTree(pll_utree ? pll_utree->tip_count : 0), _pll_utree(pll_utree.release()) {}
  Tree(std::unique_ptr<pll_utree_t>&&  pll_utree) :
    BasicTree(pll_utree ? pll_utree->tip_count : 0), _pll_utree(pll_utree.release()) {}

  Tree (const Tree& other);
  Tree& operator=(const Tree& other);
  Tree (Tree&& other);
  Tree& operator=(Tree&& other);

  virtual ~Tree();

  static Tree buildRandom(size_t num_tips, const char * const* tip_labels, unsigned int random_seed);
  static Tree buildRandom(const NameList& taxon_names, unsigned int random_seed);
  static Tree buildRandomConstrained(const NameList& taxon_names, unsigned int random_seed,
                                     const Tree& constrained_tree);
  static Tree buildParsimony(const PartitionedMSA& parted_msa, unsigned int random_seed,
                             unsigned int attributes, unsigned int * score = nullptr);
  static Tree loadFromFile(const std::string& file_name);

  std::vector<const char*> tip_labels_cstr() const;
  NameList tip_labels_list() const;
  IdNameVector tip_labels() const;
  NameIdMap tip_ids() const;

  TreeTopology topology() const;
  void topology(const TreeTopology& topol);

  const std::vector<doubleVector>& partition_brlens() const { return _partition_brlens; }
  const doubleVector& partition_brlens(size_t partition_idx) const;
  void partition_brlens(size_t partition_idx, const doubleVector& brlens);
  void partition_brlens(size_t partition_idx, doubleVector&& brlens);
  void add_partition_brlens(doubleVector&& brlens);

  // TODO: use move semantics to transfer ownership?
  const pll_utree_t& pll_utree() const { return *_pll_utree; }
  pll_utree_t * pll_utree_copy() const;
  void pll_utree(const pll_utree_t&);
  void pll_utree(unsigned int tip_count, const pll_unode_t& root);

  const pll_unode_t& pll_utree_root() const { return *_pll_utree->vroot; }
  bool empty() const { return _num_tips == 0; }

  void fix_outbound_brlens(double min_brlen, double max_brlen);
  void fix_missing_brlens(double new_brlen = RAXML_BRLEN_DEFAULT);
  void reset_brlens(double new_brlen = RAXML_BRLEN_DEFAULT);
  void collapse_short_branches(double min_brlen);
  void apply_partition_brlens(size_t partition_idx);
  void apply_avg_brlens(const doubleVector& partition_contributions);

  void reset_tip_ids(const NameIdMap& label_id_map);
  void reroot(const NameList& outgroup_taxa, bool add_root_node = false);
  void insert_tips_random(const NameList& tip_names, unsigned int random_seed = 0);

public:
  bool binary() const;
  size_t num_inner() const;
  size_t num_branches() const;

protected:
  PllUTreeUniquePtr _pll_utree;
  std::vector<doubleVector> _partition_brlens;

  mutable PllNodeVector _pll_utree_tips;

  PllNodeVector const& tip_nodes() const;
  PllNodeVector subnodes() const;
};

typedef std::vector<Tree> TreeList;
typedef std::vector<TreeTopology> TreeTopologyList;

typedef std::pair<double, TreeTopology> ScoredTopology;

class ScoredTopologyMap
{
public:
  typedef std::map<size_t, ScoredTopology> container_type;
  typedef container_type::const_iterator const_iterator;
  typedef container_type::value_type value_type;
  typedef container_type::mapped_type mapped_type;

  size_t size() const { return  _trees.size(); }
  bool empty() const { return  _trees.empty(); }
  bool contains(size_t index) const { return  _trees.count(index) > 0; }
  const_iterator best() const;
  double best_score() const { return best()->second.first; }
  const TreeTopology& best_topology() const { return best()->second.second; }

  const mapped_type& at(size_t index) const;

  const_iterator begin() const { return _trees.cbegin(); }
  const_iterator end() const { return _trees.cend(); }

  void clear() { _trees.clear(); };
  void insert(size_t index, const ScoredTopology& t) { _trees[index] = t; };

private:
  container_type _trees;
};


#endif /* RAXML_TREE_HPP_ */
