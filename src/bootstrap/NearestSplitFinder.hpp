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
#include <algorithm>

#include "../common.h"

/*
 * The algorithm for transfer bootstrap distance from the Nature paper. I had no better idea of how to name that class.
 */

typedef struct {
	unsigned int idx;
	unsigned int firstIdx;
	unsigned int lastIdx;
	unsigned int subtreeSize;
	unsigned int p;
} IndexInformation;

class NearestSplitFinder {
public:
	NearestSplitFinder() :
			_split_len(0), _nTax(0), _nTax_div_2(0), _root(NULL), _nodes_count(0), _trav_size(0) {
	}

	~NearestSplitFinder() {

	}

	void create(pll_unode_t* root, unsigned int split_len, unsigned int nTax) {
		_split_len = split_len;
		_nTax = nTax;
		_nTax_div_2 = nTax / 2;
		_root = root;
		/* allocate a buffer for storing clv_indices of the nodes in postorder
		 traversal */
		_nodes_count = 2 * nTax - 2;
		_trav_size = 0;
		idxInfos.resize(_nodes_count);
		// do a single post order traversal.
		pll_utree_traverse_sarah(root, &_trav_size);
	}

	unsigned int zerosFromTo(unsigned int start, unsigned int end, unsigned int zerosInsideSubtree,
			const RefSplitInfo& query) {
		unsigned int res = 0;
		if (end < query.leftLeafIdx) { // collect some zeros left from subtree
			res = query.subtreeRes * (end + 1 - start);
		} else if (end <= query.rightLeafIdx) {
			if (start < query.leftLeafIdx) {
				res += query.subtreeRes * ((query.leftLeafIdx - 1) + 1 - start);
				res += !query.subtreeRes * (end + 1 - query.leftLeafIdx);
			} else {
				res = !query.subtreeRes * (end + 1 - start);
			}
		} else { // end is right from the subtree
			if (start < query.leftLeafIdx) {
				res += query.subtreeRes * ((query.leftLeafIdx - 1) + 1 - start);
				res += zerosInsideSubtree;
				res += query.subtreeRes * (end + 1 - (query.rightLeafIdx + 1));
			} else if (start < query.rightLeafIdx) {
				res += !query.subtreeRes * (query.rightLeafIdx + 1 - start);
				res += query.subtreeRes * (end + 1 - (query.rightLeafIdx + 1));
			} else {
				res = query.subtreeRes * (end + 1 - start);
			}
		}
		return res;
	}

	unsigned int search_mindist(const RefSplitInfo& query) {
		unsigned int minDist = query.p - 1;
		// fast way to get prefix sum of zeros in the query, TODO: check these numbers
		unsigned int zerosInsideSubtree = (query.rightLeafIdx + 1 - query.leftLeafIdx) * !query.subtreeRes;

		for (size_t i = 0; i < _trav_size; ++i) {
			if (idxInfos[i].p <= query.p) {
				if (idxInfos[i].p <= query.p - minDist) {
					continue;
				}
			} else {
				if (idxInfos[i].p >= minDist + query.p) {
					continue;
				}
			}
			unsigned int countZeros = zerosFromTo(idxInfos[i].firstIdx, idxInfos[i].lastIdx, zerosInsideSubtree,
					query);
			unsigned int countOnes = idxInfos[i].subtreeSize - countZeros;
			unsigned int distCand = query.p - countZeros + countOnes;
			if (distCand > _nTax_div_2) {
				distCand = _nTax - distCand;
			}
			if (distCand < minDist) {
				minDist = distCand;
				if (minDist == 1) {
					return minDist;
				}
			}
		}
		return minDist;
	}
private:
	void utree_traverse_recursive_sarah(pll_unode_t * node, unsigned int * index) {
		if (node->next == NULL)
			return;
		pll_unode_t * snode = node->next;
		do {
			utree_traverse_recursive_sarah(snode->back, index);
			snode = snode->next;
		} while (snode && snode != node);
		idxInfos[*index].idx = node->clv_index;
		unsigned int idxLeft = node->next->back->clv_index;
		unsigned int idxRight = node->next->next->back->clv_index;
		idxInfos[*index].firstIdx = idxInfos[idxLeft].firstIdx;
		idxInfos[*index].lastIdx = idxInfos[idxRight].lastIdx;
		idxInfos[*index].subtreeSize = idxInfos[*index].lastIdx + 1 - idxInfos[*index].firstIdx;
		idxInfos[*index].p = std::min(idxInfos[*index].subtreeSize, _nTax - idxInfos[*index].subtreeSize);
		*index = *index + 1;
	}

	void pll_utree_traverse_sarah(pll_unode_t * root, unsigned int * trav_size) {
		*trav_size = 0;
		/* we will traverse an unrooted tree in the following way

		 2
		 /
		 1  --*
		 3

		 at each node the callback function is called to decide whether we
		 are going to traversing the subtree rooted at the specific node */
		utree_traverse_recursive_sarah(root->back, trav_size);
		utree_traverse_recursive_sarah(root, trav_size);
	}

	unsigned int _split_len;
	unsigned int _nTax;
	unsigned int _nTax_div_2;
	pll_unode_t* _root;
	unsigned int _nodes_count;
	unsigned int _trav_size;
	std::vector<IndexInformation> idxInfos;
};

#endif /* SRC_BOOTSTRAP_NEARESTSPLITFINDER_HPP_ */
