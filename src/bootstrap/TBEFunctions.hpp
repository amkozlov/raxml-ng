/*
 * TBEFunctions.hpp
 *
 *  Created on: Feb 22, 2019
 *      Author: sarah
 */

#pragma once

#include "../common.h"

typedef struct {
	unsigned int idx;
	unsigned int idxLeft;
	unsigned int idxRight;
} IndexInformation;

typedef struct {
	unsigned int p;
	bool subtreeRes;
	unsigned int leftLeafIdx;
	unsigned int rightLeafIdx;
} RefSplitInfo;

typedef struct {
	unsigned int* subtreeSize;
	IndexInformation* idxInfos;
	unsigned int nodesCount;
	unsigned int travSize;
	unsigned int nTax;
	unsigned int nTax_div_2;
} TBEData;

static int cb_full_traversal(pll_unode_t * node) {
	(void) node;
	return 1;
}

inline RefSplitInfo* initRefsplits(pll_unode_t * ref_root, unsigned int nTax, const pll_unode_t** split_to_node_map) {
	unsigned int nodes_count = 2 * nTax - 2;
	unsigned int split_count = nTax - 3;
	RefSplitInfo* split_info = (RefSplitInfo*) malloc(sizeof(RefSplitInfo) * split_count);
	unsigned int subtree_size[nodes_count];
	unsigned int aLeafIdx[nodes_count];
	unsigned int bLeafIdx[nodes_count];
	// do a post-order traversal of the reference tree.
	pll_unode_t ** travbuffer = (pll_unode_t **) malloc(nodes_count * sizeof(pll_unode_t *));
	unsigned int trav_size;
	pll_utree_traverse(ref_root, PLL_TREE_TRAVERSE_POSTORDER, cb_full_traversal, travbuffer, &trav_size);
	for (unsigned int i = 0; i < trav_size; ++i) { // first, we compute the subtree sizes.
		unsigned int idx = travbuffer[i]->clv_index;
		if (travbuffer[i]->next == NULL) { // we are at a leaf node
			subtree_size[idx] = 1;
			aLeafIdx[idx] = idx;
			bLeafIdx[idx] = idx;
		} else {
			unsigned int idxLeft = travbuffer[i]->next->back->clv_index;
			unsigned int idxRight = travbuffer[i]->next->next->back->clv_index;
			subtree_size[idx] = subtree_size[idxLeft] + subtree_size[idxRight];
			aLeafIdx[idx] = aLeafIdx[idxLeft];
			bLeafIdx[idx] = bLeafIdx[idxRight];
		}
	}
	// now we need to check for each split in the reference tree if we need to do p=subtree_size or p = n-subtree_size
	for (unsigned int i = 0; i < split_count; ++i) {
		unsigned int node_idx = split_to_node_map[i]->clv_index;
		unsigned int firstLeafIdx = aLeafIdx[node_idx];
		bool firstLeafOne = (firstLeafIdx > 0); // because taxon 0 is by convention always zero
		if (subtree_size[node_idx] <= nTax - subtree_size[node_idx]) {
			split_info[i].p = subtree_size[node_idx];
			split_info[i].subtreeRes = !firstLeafOne ? firstLeafOne : !firstLeafOne;
		} else {
			split_info[i].p = nTax - subtree_size[node_idx];
			split_info[i].subtreeRes = firstLeafOne ? firstLeafOne : !firstLeafOne;
		}
		split_info[i].leftLeafIdx = aLeafIdx[node_idx];
		split_info[i].rightLeafIdx = bLeafIdx[node_idx];
	}
	free(travbuffer);

	return split_info;
}

inline void utree_traverse_recursive_sarah(pll_unode_t * node, unsigned int * index, unsigned int * subtreeSize, IndexInformation* idxInfos) {
	if (node->next == NULL) {
		subtreeSize[node->clv_index] = 1;
		return;
	}
	pll_unode_t * snode = node->next;
	do {
		utree_traverse_recursive_sarah(snode->back, index, subtreeSize, idxInfos);
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

inline void pll_utree_traverse_sarah(pll_unode_t * root, unsigned int * trav_size, unsigned int * subtreeSize, IndexInformation* idxInfos) {
	*trav_size = 0;
	/* we will traverse an unrooted tree in the following way

	 2
	 /
	 1  --*
	 3

	 at each node the callback function is called to decide whether we
	 are going to traversing the subtree rooted at the specific node */
	utree_traverse_recursive_sarah(root->back, trav_size, subtreeSize, idxInfos);
	utree_traverse_recursive_sarah(root, trav_size, subtreeSize, idxInfos);
}

inline TBEData* init_tbe_data(pll_unode_t * root, unsigned int nTax) {
	TBEData* data = (TBEData*) malloc(sizeof(TBEData));
	data->nTax = nTax;
	data->nTax_div_2 = nTax / 2;
	data->travSize = 0;
	data->nodesCount = 2 * nTax - 2;
	data->subtreeSize = (unsigned int*) malloc(sizeof(unsigned int) * data->nodesCount);
	data->idxInfos = (IndexInformation*) malloc(sizeof(IndexInformation) * data->nodesCount);
	pll_utree_traverse_sarah(root, &data->travSize, data->subtreeSize, data->idxInfos);
	return data;
}

inline void free_tbe_data(TBEData* data) {
	free(data->subtreeSize);
	free(data->idxInfos);
	free(data);
}

inline unsigned int search_mindist(const RefSplitInfo* query, const TBEData* data, unsigned int* countOnes) {
	unsigned int minDist = query->p - 1;
	// initialize the leaf node informations...
	for (size_t i = 0; i < query->leftLeafIdx; ++i) {
		countOnes[i] = !query->subtreeRes;
	}
	for (size_t i = query->leftLeafIdx; i <= query->rightLeafIdx; ++i) {
		countOnes[i] = query->subtreeRes;
	}
	for (size_t i = query->rightLeafIdx + 1; i < data->nodesCount; ++i) {
		countOnes[i] = !query->subtreeRes;
	}

	for (size_t i = 0; i < data->travSize; ++i) {
		unsigned int idx = data->idxInfos[i].idx;
		unsigned int idxLeft = data->idxInfos[i].idxLeft;
		unsigned int idxRight = data->idxInfos[i].idxRight;
		countOnes[idx] = countOnes[idxLeft] + countOnes[idxRight];
		unsigned int countZeros = data->subtreeSize[idx] - countOnes[idx];
		unsigned int distCand = query->p - countZeros + countOnes[idx];

		if (distCand > data->nTax_div_2) {
			distCand = data->nTax - distCand;
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

inline unsigned int search_mindist(const RefSplitInfo* query, const TBEData* data) {
	unsigned int countOnes[data->nodesCount];
	return search_mindist(query, data, countOnes);
}

/* Compute Transfer Support (Lemoine et al., Nature 2018) for every split in ref_splits. Sarahs implementation of the algorithm from the Nature paper. */
PLL_EXPORT inline int pllmod_utree_split_transfer_support_nature(pll_split_t * ref_splits, pll_split_t * bs_splits, pll_unode_t* bs_root,
		unsigned int tip_count, double * support, RefSplitInfo* split_info) {
	unsigned int i;
	unsigned int split_count = tip_count - 3;

	if (!ref_splits || !bs_splits || !support || !split_info) {
		//pllmod_set_error(PLL_ERROR_PARAM_INVALID, "Parameter is NULL!\n");
		return PLL_FAILURE;
	}

	bitv_hashtable_t * bs_splits_hash = pllmod_utree_split_hashtable_insert(NULL, bs_splits, tip_count, split_count,
	NULL, 0);

	if (!bs_splits_hash) {
		return PLL_FAILURE;
	}

	TBEData* tbeData = NULL;
	unsigned int* countOnes = NULL;

	/* iterate over all splits of the reference tree */
	for (i = 0; i < split_count; i++) {
		pll_split_t ref_split = ref_splits[i];
		if (pllmod_utree_split_hashtable_lookup(bs_splits_hash, ref_split, tip_count)) {
			/* found identical split in a bootstrap tree -> assign full support */
			support[i] = 1.0;
			continue;
		}
		if (split_info[i].p == 2) { // no need for further searching
			support[i] = 0.0;
			continue;
		}
		if (tbeData == NULL) {
			tbeData = init_tbe_data(bs_root, tip_count);
			countOnes = (unsigned int*) malloc(sizeof(unsigned int) * tbeData->nodesCount);
		}
		// else, we are in the search for minimum distance...
		unsigned int min_hdist = search_mindist(&split_info[i], tbeData, countOnes);
		//assert(min_hdist > 0);
		support[i] = 1.0 - (((double) min_hdist) / (split_info[i].p - 1));
	}

	pllmod_utree_split_hashtable_destroy(bs_splits_hash);

	if (tbeData != NULL) {
		free_tbe_data(tbeData);
	}
	if (countOnes != NULL) {
		free(countOnes);
	}

	return PLL_SUCCESS;
}

