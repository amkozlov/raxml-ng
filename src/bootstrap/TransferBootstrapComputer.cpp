/*
 * TransferBootstrapComputer.cpp
 *
 *  Created on: Jan 16, 2019
 *      Author: sarah
 */

#include "TransferBootstrapComputer.hpp"
#include "VPTree.hpp"
#include "SimpleMVPTree.hpp"
#include "NearestSplitFinder.hpp"

#include <chrono>

bool split_info_filled = false;
std::vector<RefSplitInfo> split_info;

inline unsigned int bitv_length(unsigned int bit_count) {
	unsigned int split_size = sizeof(pll_split_base_t) * 8;
	unsigned int split_offset = bit_count % split_size;

	return bit_count / split_size + (split_offset > 0);
}

static int cb_full_traversal(pll_unode_t * node) {
	(void) node;
	return 1;
}

/* Compute Transfer Support (Lemoine et al., Nature 2018) for every split in ref_splits. Sarahs implementation of the algorithm from the Nature paper. */
PLL_EXPORT int pllmod_utree_split_transfer_support_nature(pll_split_t * ref_splits, pll_split_t * bs_splits, pll_unode_t* bs_root,
		unsigned int tip_count, double * support, const std::vector<pll_unode_t*>& split_to_node_map, pll_unode_t * ref_root) {
	unsigned int i;
	unsigned int split_count = tip_count - 3;
	unsigned int split_len = bitv_length(tip_count);

	if (!split_info_filled) {
		unsigned int nodes_count = 2 * tip_count - 2;
		std::vector<unsigned int> subtree_size(nodes_count);
		std::vector<unsigned int> aLeafIdx(nodes_count);
		std::vector<unsigned int> bLeafIdx(nodes_count);
		split_info.resize(split_count);
		// first, instead of p we store the subtree size in that one.
		// do a post-order traversal of the reference tree.
		pll_unode_t ** travbuffer = (pll_unode_t **) malloc(nodes_count * sizeof(pll_unode_t *));
		unsigned int trav_size;
		pll_utree_traverse(ref_root, PLL_TREE_TRAVERSE_POSTORDER, cb_full_traversal, travbuffer, &trav_size);
		for (i = 0; i < trav_size; ++i) { // first, we compute the subtree sizes.
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
		for (i = 0; i < split_count; ++i) {
			unsigned int node_idx = split_to_node_map[i]->clv_index;
			unsigned int firstLeafIdx = aLeafIdx[node_idx];
			// we need to check if the split at firstLeafIdx is zero or one
			bool firstLeafOne;
			// 1) find the correct 32-bit-number that contains the bit in question
			unsigned int numberIdx = firstLeafIdx / 32;
			// 2) find the correct bit in this number that is the bit in question
			unsigned int bitIdx = firstLeafIdx - (numberIdx * 32);
			// 3) read this bit into res
			firstLeafOne = (ref_splits[i][numberIdx] >> bitIdx) & 1;

			if (subtree_size[node_idx] <= tip_count - subtree_size[node_idx]) {
				split_info[i].p = subtree_size[node_idx];
				split_info[i].subtreeRes = !firstLeafOne ? firstLeafOne : !firstLeafOne;

			} else {
				split_info[i].p = tip_count - subtree_size[node_idx];
				split_info[i].subtreeRes = firstLeafOne ? firstLeafOne : !firstLeafOne;
			}
			split_info[i].leftLeafIdx = aLeafIdx[node_idx];
			split_info[i].rightLeafIdx = bLeafIdx[node_idx];
		}
		delete travbuffer;
		split_info_filled = true;
	}

	if (!ref_splits || !bs_splits || !support) {
		//pllmod_set_error(PLL_ERROR_PARAM_INVALID, "Parameter is NULL!\n");
		return PLL_FAILURE;
	}

	bitv_hashtable_t * bs_splits_hash = pllmod_utree_split_hashtable_insert(NULL, bs_splits, tip_count, split_count,
	NULL, 0);

	if (!bs_splits_hash) {
		return PLL_FAILURE;
	}

	NearestSplitFinder splitFinder;
	bool index_constructed = false;

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
		if (!index_constructed) {
			splitFinder.create(bs_root, split_len, tip_count);
			index_constructed = true;
		}
		// else, we are in the search for minimum distance...
		unsigned int min_hdist = splitFinder.search_mindist(split_info[i]);
		//assert(min_hdist > 0);
		support[i] = 1.0 - (((double) min_hdist) / (split_info[i].p - 1));
	}

	pllmod_utree_split_hashtable_destroy(bs_splits_hash);

	return PLL_SUCCESS;
}

/* Compute Transfer Support (Lemoine et al., Nature 2018) for every split in ref_splits. Sarahs version with MVP-Trees. */
PLL_EXPORT int pllmod_utree_split_transfer_support_sarah(pll_split_t * ref_splits, pll_split_t * bs_splits, unsigned int tip_count,
		double * support) {
	if (!wordbits_filled) {
		popcount32e_init();
		wordbits_filled = true;
	}
	unsigned int i;
	unsigned int split_count = tip_count - 3;
	unsigned int split_len = bitv_length(tip_count);
	unsigned int split_size = sizeof(pll_split_base_t) * 8;
	unsigned int split_offset = tip_count % split_size;
	unsigned int split_mask = split_offset ? (1 << split_offset) - 1 : ~0;

	if (!ref_splits || !bs_splits || !support) {
		//pllmod_set_error(PLL_ERROR_PARAM_INVALID, "Parameter is NULL!\n");
		return PLL_FAILURE;
	}

	bitv_hashtable_t * bs_splits_hash = pllmod_utree_split_hashtable_insert(NULL, bs_splits, tip_count, split_count,
	NULL, 0);

	if (!bs_splits_hash) {
		return PLL_FAILURE;
	}

	//auto start = std::chrono::high_resolution_clock::now();
	// precompute all inverse bootstrap splits
	pll_split_t * inv_bs_splits = (pll_split_t *) malloc(split_count * sizeof(pll_split_t));
	if (!inv_bs_splits) {
		return PLL_FAILURE;
	}
	for (size_t i = 0; i < split_count; ++i) {
		/* inverse the bs split */
		pll_split_t inv_split = (pll_split_t) calloc(split_len, sizeof(pll_split_base_t));
		if (!inv_split) {
			return PLL_FAILURE;
		}
		for (size_t k = 0; k < split_len; ++k) {
			inv_split[k] = ~bs_splits[i][k];
		}
		/* clear unused bits in the last array element */
		inv_split[split_len - 1] &= split_mask;
		inv_bs_splits[i] = inv_split;
	}

	SimpleMvpTree bsVPTree;
	bool index_constructed = false;
	//unsigned long int total_query_time = 0;

	/* iterate over all splits of the reference tree */
	for (i = 0; i < split_count; i++) {
		pll_split_t ref_split = ref_splits[i];

		if (pllmod_utree_split_hashtable_lookup(bs_splits_hash, ref_split, tip_count)) {
			/* found identical split in a bootstrap tree -> assign full support */
			support[i] = 1.0;
			continue;
		}

		unsigned int p = pllmod_utree_split_lightside_sarah(ref_split, tip_count);

		if (p == 2) { // no need for further searching
			support[i] = 0.0;
			continue;
		}

		unsigned int min_hdist = p - 1;

		if (!index_constructed) {
			//auto start = std::chrono::high_resolution_clock::now();
			bsVPTree.create(bs_splits, inv_bs_splits, split_len, split_count, tip_count);
			//auto mid = std::chrono::high_resolution_clock::now();
			//std::cout << "Runtime VP-Tree construction: " << std::chrono::duration_cast<std::chrono::microseconds>(mid - start).count() << std::endl;
			index_constructed = true;
		}

		// else, we are in the search for minimum distance...
		//auto s1 = std::chrono::high_resolution_clock::now();
		min_hdist = bsVPTree.search_mindist(ref_split, p);
		//auto e1 = std::chrono::high_resolution_clock::now();
		//total_query_time += std::chrono::duration_cast<std::chrono::microseconds>(e1 - s1).count();

		//std::cout << "minimum distance found Sarah: " << min_hdist << "\n";

		assert(min_hdist > 0);
		support[i] = 1.0 - (((double) min_hdist) / (p - 1));
	}

	//auto end = std::chrono::high_resolution_clock::now();
	//std::cout << "Runtime VP-Tree queries: " << total_query_time << std::endl;

	pllmod_utree_split_hashtable_destroy(bs_splits_hash);
	free(inv_bs_splits);

	return PLL_SUCCESS;
}
