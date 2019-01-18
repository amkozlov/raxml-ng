/*
 * VPTree.hpp
 *
 *  Created on: Jan 15, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_VPTREE_HPP_
#define SRC_BOOTSTRAP_VPTREE_HPP_

// A VP-Tree implementation, by Steve Hanov. (steve.hanov@gmail.com)
// Released to the Public Domain
// Based on "Data Structures and Algorithms for Nearest Neighbor Search" by Peter N. Yianilos

// Adapted from http://stevehanov.ca/blog/index.php?id=130 by Sarah.

#include <bits/move.h>
#include <stddef.h>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include "../../build/localdeps/include/libpll/pll.h"
#include "../../build/localdeps/include/libpll/pll_tree.h"

inline std::string split_string(pll_split_t split) {
	std::string binary = std::bitset<20>(*split).to_string();
	return binary;
}

static const unsigned int BUCKET_SIZE = 100;

class VpTree {
public:
	VpTree() :
			_split_len(0), _splits(0), _inv_splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _nTax_div_2(0), _root(0) {
	}

	~VpTree() {
		delete _root;
	}

	void create(pll_split_t * splits, pll_split_t * inv_splits, size_t split_len, size_t num_splits, size_t nTax) {
		delete _root;
		_split_len = split_len;
		_splits = splits;
		_inv_splits = inv_splits;
		_nTax = nTax;
		_nTax_div_2 = _nTax / 2;

		_bs_light.resize(num_splits);
		// precompute lightside size for all bootstrap splits
		for (unsigned int j = 0; j < num_splits; j++) {
			_bs_light[j] = pllmod_utree_split_lightside(splits[j], nTax);
		}

		_items.resize(num_splits);
		for (size_t i = 0; i < num_splits; ++i) {
			_items[i] = i;
		}

		std::vector<unsigned int> dist_to_lower(_items.size());
		_root = buildFromPoints(0, _items.size(), dist_to_lower);
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		_tau = p - 1;
		search(_root, target, p);
		/*
		 // check if the result is correct
		 size_t min_idx = 0;
		 unsigned int min = p - 1;
		 for (size_t i = 0; i < _items.size(); ++i) {
		 unsigned int dist = distance(target, _splits[i], _split_len, _nTax);
		 if (dist < min) {
		 min = dist;
		 min_idx = i;
		 }
		 }
		 if (_tau != min) {
		 std::cout << "ERROR!!! THE RESULT IS WRONG!!!\n";
		 std::cout << "_tau: " << _tau << "\n";
		 std::cout << "min: " << min << "\n";
		 std::cout << "p-1: " << p - 1 << "\n";
		 }
		 */
		return _tau;
	}

private:
	unsigned int _split_len;
	pll_split_t * _splits;
	pll_split_t * _inv_splits;
	std::vector<unsigned int> _bs_light;
	std::vector<unsigned int> _items;
	unsigned int _tau;
	unsigned int _nTax;
	unsigned int _nTax_div_2;

	/* This function computes a lower bound of Hamming distance between splits:
	 * the computation terminates as soon as current distance values exceeds min_hdist.
	 * This allows for substantial time savings if we are looking for the
	 * minimum Hamming distance (as in TBE computation below).
	 *
	 * WARNING: This function does not check that hdist < N/2. Therefore,
	 * it should be called twice, with original and inverted s1 (or s2),
	 * to account for possible complementary split encoding.
	 * */
	unsigned int split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int min_hdist) {
		unsigned int hdist = 0;
		unsigned int i;

		for (i = 0; (i < _split_len) && (hdist <= min_hdist); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}

		return hdist;
	}

	void split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int min_hdist,
			unsigned int& hdist, unsigned int& i) {
		for (; (i < _split_len) && (hdist <= min_hdist); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}
	}

	unsigned int split_hamming_distance(pll_split_t s1, pll_split_t s2) {
		unsigned int hdist = 0;
		unsigned int i;

		for (i = 0; (i < _split_len); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}

		return hdist;
	}

	unsigned int distance(pll_split_t s1, pll_split_t s1_inv, pll_split_t s2,
			unsigned int max_interesting_distance) {
		unsigned int dist = split_hamming_distance_lbound(s1, s2, max_interesting_distance);
		if (dist <= _nTax_div_2 && dist < max_interesting_distance) {
			return dist;
		}
		unsigned int dist_inv = split_hamming_distance_lbound(s1_inv, s2, max_interesting_distance);
		return std::min(dist, dist_inv);
	}

	unsigned int distance(pll_split_t s1, pll_split_t s1_inv, pll_split_t s2,
			unsigned int max_interesting_distance, unsigned int &old_dist_forward, unsigned int& old_dist_reverse,
			unsigned int& old_i_forward, unsigned int& old_i_reverse, unsigned int minDist) {
		if (minDist > max_interesting_distance || std::min(old_dist_forward, old_dist_reverse) > max_interesting_distance) {
			return max_interesting_distance + 1;
		}
		split_hamming_distance_lbound(s1, s2, max_interesting_distance, old_dist_forward, old_i_forward);
		if (old_dist_forward <= _nTax_div_2 && old_dist_forward < max_interesting_distance) {
			return old_dist_forward;
		}
		split_hamming_distance_lbound(s1_inv, s2, max_interesting_distance, old_dist_reverse, old_i_reverse);
		return std::min(old_dist_forward, old_dist_reverse);
	}

	unsigned int distance(pll_split_t s1, pll_split_t s2) {
		unsigned int dist = split_hamming_distance(s1, s2);
		return std::min(dist, _nTax - dist);
	}

	struct Node {
		int index;
		std::vector<unsigned int> bucketEntries;
		unsigned int threshold;
		Node* left;
		Node* right;

		Node() :
				index(0), threshold(0.), left(0), right(0) {
		}

		~Node() {
			delete left;
			delete right;
		}
	}* _root;

	struct DistanceComparator {
		const std::vector<unsigned int>& _dist_to_lower;
		DistanceComparator(const std::vector<unsigned int>& dist_to_lower) :
				_dist_to_lower(dist_to_lower) {
		}
		bool operator()(const unsigned int& a, const unsigned int& b) {
			return _dist_to_lower[a] < _dist_to_lower[b];
		}
	};

	Node* buildFromPoints(unsigned int lower, unsigned int upper, std::vector<unsigned int>& dist_to_lower) {
		if (upper == lower) {
			return NULL;
		}

		Node* node = new Node();
		node->index = lower;

		if (upper - lower <= BUCKET_SIZE) {
			node->bucketEntries.reserve(BUCKET_SIZE - 1);
			// just add all these elements to the node's bucket.
			node->index = lower;
			for (size_t i = lower + 1; i < upper; ++i) {
				node->bucketEntries.push_back(i);
			}
		} else if (upper > lower + 1) {
			// choose an arbitrary point and move it to the start
			//int i = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			std::swap(_items[lower], _items[upper - 1]);

			unsigned int median = (upper + lower) / 2;

			// precompute dist_to_lower once
			for (size_t i = lower + 1; i < upper; ++i) {
				unsigned int dist = distance(_splits[_items[lower]], _inv_splits[_items[lower]], _splits[_items[i]],
						_nTax_div_2);

				dist_to_lower[_items[i]] = dist;
			}

			// partition around the median distance
			std::nth_element(_items.begin() + lower + 1, _items.begin() + median, _items.begin() + upper,
					DistanceComparator(dist_to_lower));

			// what was the median?
			node->threshold = distance(_splits[_items[lower]], _splits[_items[median]]);
			/*std::cout << "Median distance was: " << node->threshold << " " << "nTax/2 is: " << _nTax / 2 << " nItems is: " << upper - lower
			 << "\n";*/

			node->index = lower;
			node->left = buildFromPoints(lower + 1, median, dist_to_lower);
			node->right = buildFromPoints(median, upper, dist_to_lower);
		}

		return node;
	}

	void search_no_child_null(Node* node, pll_split_t target, unsigned int p, unsigned int minDist) {
		unsigned int old_dist_forward = 0;
		unsigned int old_dist_reverse = 0;
		unsigned int old_i_forward = 0;
		unsigned int old_i_reverse = 0;
		if (minDist < _tau) {
			// check if we need to update _tau before continuing...
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _tau,
					old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			_tau = std::min(_tau, dist);
			if (_tau == 1) {
				return;
			}
		}

		// checks for right node
		if (minDist + _tau >= node->threshold) {
			search(node->right, target, p);
		} else {
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target,
					node->threshold - _tau, old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			if (dist + _tau >= node->threshold) {
				search(node->right, target, p);
			}
		}

		// checks for left node
		if (minDist <= node->threshold + _tau) {
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target,
					node->threshold + _tau, old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			if (dist <= node->threshold + _tau) {
				search(node->left, target, p);
			}
		}
	}

	void search_right_child_null(Node* node, pll_split_t target, unsigned int p, unsigned int minDist) {
		unsigned int old_dist_forward = 0;
		unsigned int old_dist_reverse = 0;
		unsigned int old_i_forward = 0;
		unsigned int old_i_reverse = 0;
		if (minDist < _tau) {
			// check if we need to update _tau before continuing...
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _tau,
					old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			_tau = std::min(_tau, dist);
			if (_tau == 1) {
				return;
			}
		}

		if (minDist <= node->threshold + _tau) {
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target,
					node->threshold + _tau, old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			if (dist <= node->threshold + _tau) {
				search(node->left, target, p);
			}
		}
	}

	void search_left_child_null(Node* node, pll_split_t target, unsigned int p, unsigned int minDist) {
		unsigned int old_dist_forward = 0;
		unsigned int old_dist_reverse = 0;
		unsigned int old_i_forward = 0;
		unsigned int old_i_reverse = 0;
		if (minDist < _tau) {
			// check if we need to update _tau before continuing...
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _tau,
					old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			_tau = std::min(_tau, dist);
			if (_tau == 1) {
				return;
			}
		}

		if (minDist + _tau >= node->threshold) {
			search(node->right, target, p);
		} else {
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target,
					node->threshold - _tau, old_dist_forward, old_dist_reverse, old_i_forward, old_i_reverse, minDist);
			//printf("dist=%g tau=%gn", dist, _tau );
			if (dist + _tau >= node->threshold) {
				search(node->right, target, p);
			}
		}
	}

	void search_both_children_null(Node* node, pll_split_t target, unsigned int p, unsigned int minDist) {
		if (minDist < _tau) {
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _tau);
			_tau = std::min(_tau, dist);
			if (_tau == 1) {
				return;
			}
		}
		for (size_t i = 0; i < node->bucketEntries.size(); ++i) {
			unsigned int actMinDist;
			if (p >= _bs_light[_items[node->bucketEntries[i]]]) {
				actMinDist = p - _bs_light[_items[node->bucketEntries[i]]];
			} else {
				actMinDist = _bs_light[_items[node->bucketEntries[i]]] - p;
			}
			if (actMinDist < _tau) {
				unsigned int dist = distance(_splits[_items[node->bucketEntries[i]]], _inv_splits[_items[node->bucketEntries[i]]], target, _tau);
				_tau = std::min(_tau, dist);
				if (_tau == 1) {
					return;
				}
			}
		}
	}

	void search(Node* node, pll_split_t target, unsigned int p) {
		if (node == NULL || _tau == 1) {
			return;
		}
		unsigned int minDist;
		if (p >= _bs_light[_items[node->index]]) {
			minDist = p - _bs_light[_items[node->index]];
		} else {
			minDist = _bs_light[_items[node->index]] - p;
		}
		//minDist = std::min(minDist, _nTax - minDist);

		if (node->left == NULL && node->right == NULL) { // both children are NULL, nothing left to do. We just search the entire bucket...
			search_both_children_null(node, target, p, minDist);
		} else if (node->left == NULL) {
			search_left_child_null(node, target, p, minDist);
		} else if (node->right == NULL) {
			search_right_child_null(node, target, p, minDist);
		} else {
			search_no_child_null(node, target, p, minDist);
		}
	}
};

#endif /* SRC_BOOTSTRAP_VPTREE_HPP_ */
