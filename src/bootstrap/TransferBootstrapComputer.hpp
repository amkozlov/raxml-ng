/*
 * TransferBootstrapComputer.hpp
 *
 *  Created on: Jan 16, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_TRANSFERBOOTSTRAPCOMPUTER_HPP_
#define SRC_BOOTSTRAP_TRANSFERBOOTSTRAPCOMPUTER_HPP_

#include "../common.h"

PLL_EXPORT int pllmod_utree_split_transfer_support_nature(pll_split_t * ref_splits, pll_split_t * bs_splits, pll_unode_t* bs_root, unsigned int tip_count, double * support, const pll_unode_t** split_to_node_map, pll_unode_t * ref_root);

#endif /* SRC_BOOTSTRAP_TRANSFERBOOTSTRAPCOMPUTER_HPP_ */
