/*
 * TransferBootstrapComputer.cpp
 *
 *  Created on: Jan 16, 2019
 *      Author: sarah
 */

#include "TransferBootstrapComputer.hpp"
#include "VPTree.hpp"

inline unsigned int bitv_length(unsigned int bit_count) {
	unsigned int split_size = sizeof(pll_split_base_t) * 8;
	unsigned int split_offset = bit_count % split_size;

	return bit_count / split_size + (split_offset > 0);
}

/* Compute Transfer Support (Lemoine et al., Nature 2018) for every split in ref_splits. Sarahs version with VP-Trees. */
PLL_EXPORT int pllmod_utree_split_transfer_support_sarah(pll_split_t * ref_splits, pll_split_t * bs_splits, unsigned int tip_count,
		double * support) {
	unsigned int i, j;
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

	int * bs_light = (int*) calloc(split_count, sizeof(int));
	if (!bs_light) {
		pllmod_utree_split_hashtable_destroy(bs_splits_hash);
		//pllmod_set_error(PLL_ERROR_MEM_ALLOC, "Cannot allocate memory\n");
		return PLL_FAILURE;
	}
	// precompute lightside size for all bootstrap splits
	for (j = 0; j < split_count; j++) {
		bs_light[j] = pllmod_utree_split_lightside(bs_splits[j], tip_count);
	}

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

	VpTree bsVPTree;
	bsVPTree.create(bs_splits, inv_bs_splits, split_len, split_count, tip_count);

	/* iterate over all splits of the reference tree */
	for (i = 0; i < split_count; i++) {
		pll_split_t ref_split = ref_splits[i];
		unsigned int p = pllmod_utree_split_lightside(ref_split, tip_count);

		if (p == 2) { // no need for further searching
			support[i] = 0.0;
			continue;
		}

		if (pllmod_utree_split_hashtable_lookup(bs_splits_hash, ref_split, tip_count)) {
			/* found identical split in a bootstrap tree -> assign full support */
			support[i] = 1.0;
			continue;
		}

		// else, we are in the search for minimum distance...
		unsigned int min_hdist = bsVPTree.search_mindist(ref_split, p);

		//std::cout << "minimum distance found Sarah: " << min_hdist << "\n";

		assert(min_hdist > 0);
		support[i] = 1.0 - (((double) min_hdist) / (p - 1));
	}

	pllmod_utree_split_hashtable_destroy(bs_splits_hash);
	//free(bs_light);

	return PLL_SUCCESS;
}
