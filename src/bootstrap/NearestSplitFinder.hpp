/*
 * NearestSplitFinder.hpp
 *
 *  Created on: Jan 28, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_NEARESTSPLITFINDER_HPP_
#define SRC_BOOTSTRAP_NEARESTSPLITFINDER_HPP_

#include <stdlib.h>
#include <vector>
#include <iostream>

#include "../common.h"

/*
 * The algorithm for transfer bootstrap distance from the Nature paper. I had no better idea of how to name that class.
 */

class NearestSplitFinder {
public:
	NearestSplitFinder() :
			_split_len(0), _nTax(0), _root(NULL), _travbuffer(NULL), _nodes_count(0), _trav_size(0) {
	}

	~NearestSplitFinder() {
		delete _travbuffer;
	}

	void create(pll_unode_t* root, unsigned int split_len, unsigned int nTax) {
		_split_len = split_len;
		_nTax = nTax;
		_root = root;
		/* allocate a buffer for storing pointers to nodes of the tree in postorder
		 traversal */
		_nodes_count = 2 * nTax - 2;
		counts.resize(_nodes_count * 3);
		_travbuffer = (pll_unode_t **) malloc(_nodes_count * sizeof(pll_unode_t *));
		// do a single post order traversal.
		pll_utree_traverse(root, PLL_TREE_TRAVERSE_POSTORDER, cb_full_traversal, _travbuffer, &_trav_size);
	}

	unsigned int search_mindist(pll_split_t query, unsigned int p, bool lightsideIsZeros) {
			//std::cout << "p is: " << p << "\n";
			unsigned int minDist = p - 1;
			//std::cout << "Initial minDist: " << minDist << "\n";

			//std::vector<std::array<unsigned int, 2> > counts(_nodes_count * 3); // counts[i][0] for the number of zeros, counts[i][1] for the number of ones.
			for (size_t i = 0; i < _trav_size; ++i) {
				unsigned int idx = _travbuffer[i]->node_index;
				if (!_travbuffer[i]->next) { // we are at a leaf node
					//std::cout << "I am at a leaf with index " << idx << "\n";
					bool isOne = check_bipartition_at(query, idx, lightsideIsZeros);
					if (isOne) {
						counts[idx][1] = 1;
					} else {
						counts[idx][0] = 1;
					}
				} else {
					// collect the number of ones and zeros from the child nodes
					unsigned int idxLeft = _travbuffer[i]->next->back->node_index;
					unsigned int idxRight = _travbuffer[i]->next->next->back->node_index;
					//assert(counts[idxLeft][0] + counts[idxLeft][1] > 0);
					//assert(counts[idxRight][0] + counts[idxRight][1] > 0);
					counts[idx][0] = counts[idxLeft][0] + counts[idxRight][0];
					counts[idx][1] = counts[idxLeft][1] + counts[idxRight][1];
					unsigned int actDist = std::min(p - counts[idx][0] + counts[idx][1], _nTax - p - counts[idx][1] + counts[idx][0]); // TODO: Avoid unsigned int underflow issues here.
					if (actDist < minDist) {
						minDist = actDist;
						if (minDist == 1) {
							return minDist;
						}
					}
				}
			}
			return minDist;
		}
private:
	bool check_bipartition_at(pll_split_t query, unsigned int idx, bool lightsideIsZeros) {
		bool res;
		// 1) find the correct 32-bit-number that contains the bit in question
		unsigned int numberIdx = idx / 32;
		// 2) find the correct bit in this number that is the bit in question
		unsigned int bitIdx = idx - (numberIdx * 32);
		// 3) read this bit into res
		res = (query[numberIdx] >> bitIdx) & 1;
		if (!lightsideIsZeros) {
			res = !res;
		}
		return res;
	}

	static int cb_full_traversal(pll_unode_t * node) {
		(void) node;
		return 1;
	}

	unsigned int _split_len;
	unsigned int _nTax;
	pll_unode_t* _root;
	pll_unode_t ** _travbuffer;
	unsigned int _nodes_count;
	unsigned int _trav_size;
	std::vector<std::array<unsigned int, 2> > counts; // counts[i][0] for the number of zeros, counts[i][1] for the number of ones.
};

#endif /* SRC_BOOTSTRAP_NEARESTSPLITFINDER_HPP_ */
