#ifndef RAXML_TREE_HPP_
#define RAXML_TREE_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"

struct TreeBranch
{
  TreeBranch() : left_node_id(0), right_node_id(0), length(0.) {};
  TreeBranch(size_t left_node_id, size_t right_node_id, double length) :
    left_node_id(left_node_id), right_node_id(right_node_id), length(length) {};

  size_t left_node_id;
  size_t right_node_id;
  double length;
};

typedef std::vector<TreeBranch> TreeTopology;

//struct Topology
//{
//  std::vector
//};

typedef std::vector<pll_utree_t*> PllTreeVector;

class Tree
{
public:
  Tree() : _num_tips(0), _pll_utree_start(nullptr) {};
  Tree(size_t num_tips, pll_utree_t* pll_utree_start) :
    _num_tips(num_tips), _pll_utree_start(pll_utree_clone(pll_utree_start)) {};

  Tree (const Tree& other) = default;
  Tree& operator=(const Tree& other);
  Tree (Tree&& other);
  Tree& operator=(Tree&& other);

  virtual ~Tree();

  static Tree buildRandom(size_t num_tips, const char * const* tip_labels);
  static Tree buildParsimony(const PartitionedMSA& parted_msa, unsigned int random_seed,
                             unsigned int attributes, unsigned int * score = nullptr);
  static Tree loadFromFile(const std::string& file_name);

  bool empty() const { return _num_tips == 0; };
  size_t num_tips() const { return _num_tips; };
  size_t num_inner() const { return _num_tips - 2; };
  size_t num_nodes() const { return _num_tips + _num_tips - 2; };
  size_t num_subnodes() const { return _num_tips + num_inner() * 3; };
  size_t num_branches() const { return _num_tips + _num_tips - 3; };
  IdNameVector tip_labels() const;

  TreeTopology topology() const;
  void topology(const TreeTopology& topol);

  // TODO: use move semantics to transfer ownership?
  pll_utree_t * pll_utree_copy() const { return pll_utree_clone(_pll_utree_start); };
  const pll_utree_t& pll_utree_start() const { return *_pll_utree_start; };

  void fix_missing_brlens(double new_brlen = RAXML_BRLEN_DEFAULT);
  void reset_tip_ids(const NameIdMap& label_id_map);

private:
  size_t _num_tips;
  pll_utree_t* _pll_utree_start;

  mutable PllTreeVector _pll_utree_tips;

  PllTreeVector const& tip_nodes() const;
  PllTreeVector subnodes() const;
};

#endif /* RAXML_TREE_HPP_ */
