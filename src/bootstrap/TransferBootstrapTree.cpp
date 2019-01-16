#include "TransferBootstrapTree.hpp"

#include "TransferBootstrapComputer.hpp"

#include <chrono>

TransferBootstrapTree::TransferBootstrapTree(const Tree& tree) :
		BootstrapTree(tree) {
}

TransferBootstrapTree::~TransferBootstrapTree() {
}

static const bool RUN_SARAH = true;

void TransferBootstrapTree::add_boot_splits_to_hashtable(const pll_unode_t& root) {
	doubleVector tbe(num_splits(), 1.0);

	assert(_ref_splits);

	pll_split_t * splits = pllmod_utree_split_create((pll_unode_t*) &root, _num_tips, nullptr);

	if (RUN_SARAH) {
		// compute TBE, Sarah version
		pllmod_utree_split_transfer_support_sarah(_ref_splits.get(), splits, _num_tips, tbe.data());
	} else {
		// compute TBE, Alexey version
		pllmod_utree_split_transfer_support(_ref_splits.get(), splits, _num_tips, tbe.data());
	}

	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
	pllmod_utree_split_destroy(splits);

	_pll_splits_hash = pllmod_utree_split_hashtable_insert(_pll_splits_hash, _ref_splits.get(), _num_tips, num_splits(), tbe.data(),
			1 /* update_only */);
}
