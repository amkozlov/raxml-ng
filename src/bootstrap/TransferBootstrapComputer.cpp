/*
 * TransferBootstrapComputer.cpp
 *
 *  Created on: Jan 16, 2019
 *      Author: sarah
 */

#include "TransferBootstrapComputer.hpp"
#include "TBEFunctions.hpp"

RefSplitInfo* split_info = NULL;

/* Compute Transfer Support (Lemoine et al., Nature 2018) for every split in ref_splits. Sarahs implementation of the algorithm from the Nature paper. */
PLL_EXPORT int pllmod_utree_split_transfer_support_nature(pll_split_t * ref_splits, pll_split_t * bs_splits, pll_unode_t* bs_root,
		unsigned int tip_count, double * support, const pll_unode_t** split_to_node_map, pll_unode_t * ref_root) {
	unsigned int i;
	unsigned int split_count = tip_count - 3;

	if (split_info == NULL) {
		split_info = initRefsplits(ref_root, tip_count, split_to_node_map);
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
