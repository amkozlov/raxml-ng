#ifndef RAXML_TREE_HPP_
#define RAXML_TREE_HPP_

#include "common.h"
#include "PartitionedMSA.hpp"

class Tree
{
public:
  Tree() : _pll_utree_start(nullptr), _num_tips(0) {};

  Tree (const Tree& other) = delete;
  Tree& operator=(const Tree& other) = delete;
  Tree (Tree&& other) = default;
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
  size_t num_branches() const { return _num_tips + _num_tips - 3; };
  IdNameVector tip_labels() const;

  // TODO: use move semantics to transfer ownership?
  pll_utree_t * pll_utree_start() const { return pll_utree_clone(_pll_utree_start); };

  void fix_missing_brlens(double new_brlen = RAXML_BRLEN_DEFAULT);

private:
  pll_utree_t* _pll_utree_start;
  size_t _num_tips;

  mutable std::vector<pll_utree_t*> _pll_utree_tips;

  std::vector<pll_utree_t*> const& tip_nodes() const;
};

#endif /* RAXML_TREE_HPP_ */
