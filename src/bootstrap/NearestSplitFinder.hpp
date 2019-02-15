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

#include "../common.h"

/*
 * The algorithm for transfer bootstrap distance from the Nature paper. I had no better idea of how to name that class.
 */

typedef struct {
	unsigned int idx;
	unsigned int idxLeft;
	unsigned int idxRight;
} IndexInformation;

class NearestSplitFinder {
public:
	NearestSplitFinder() :
			_split_len(0), _nTax(0), _nTax_div_2(0), _root(NULL), _nodes_count(0), _trav_size(0), idxInfos(NULL), subtreeSize(NULL), countOnes(NULL) {
	}

	~NearestSplitFinder() {
		free(idxInfos);
		free(countOnes);
		free(subtreeSize);
	}

	void create(pll_unode_t* root, unsigned int split_len, unsigned int nTax) {
		_split_len = split_len;
		_nTax = nTax;
		_nTax_div_2 = nTax / 2;
		_root = root;
		_nodes_count = 2 * nTax - 2;
		_trav_size = 0;
		/* allocate a buffer for storing clv_indices of the nodes in postorder
		 traversal */
		idxInfos = (IndexInformation*) malloc(_nodes_count * sizeof(IndexInformation));
		subtreeSize = (unsigned int*) malloc(_nodes_count * sizeof(unsigned int));
		countOnes = (unsigned int*) malloc(_nodes_count * sizeof(unsigned int));
		// do a single post order traversal.
		pll_utree_traverse_sarah(root, &_trav_size);
	}

	unsigned int search_mindist(const RefSplitInfo& query) {
		unsigned int minDist = query.p - 1;
		// initialize the leaf node informations...
		for (size_t i = 0; i < query.leftLeafIdx; ++i) {
			countOnes[i] = !query.subtreeRes;
		}
		for (size_t i = query.leftLeafIdx; i <= query.rightLeafIdx; ++i) {
			countOnes[i] = query.subtreeRes;
		}
		for (size_t i = query.rightLeafIdx + 1; i < _nodes_count; ++i) {
			countOnes[i] = !query.subtreeRes;
		}

		// maybe a level-order-traversal would be better?
		for (size_t i = 0; i < _trav_size; ++i) { // TODO: This should be possible to vectorize.
			unsigned int idx = idxInfos[i].idx;
			unsigned int idxLeft = idxInfos[i].idxLeft;
			unsigned int idxRight = idxInfos[i].idxRight;
			countOnes[idx] = countOnes[idxLeft] + countOnes[idxRight];
			unsigned int countZeros = subtreeSize[idx] - countOnes[idx];
			unsigned int distCand = query.p - countZeros + countOnes[idx];

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
		if (node->next == NULL) {
			subtreeSize[node->clv_index] = 1;
			return;
		}
		pll_unode_t * snode = node->next;
		do {
			utree_traverse_recursive_sarah(snode->back, index);
			snode = snode->next;
		} while (snode && snode != node);
		IndexInformation info;
		info.idx = node->clv_index;
		info.idxLeft = node->next->back->clv_index;
		info.idxRight = node->next->next->back->clv_index;
		subtreeSize[node->clv_index] = subtreeSize[info.idxLeft] + subtreeSize[info.idxRight];
		idxInfos[*index] = info;
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

	IndexInformation* idxInfos;
	unsigned int* subtreeSize;
	unsigned int* countOnes; // stores the number of ones in the subtrees
};

#endif /* SRC_BOOTSTRAP_NEARESTSPLITFINDER_HPP_ */
