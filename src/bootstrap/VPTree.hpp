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

#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <queue>
#include <limits>

#include <bitset>
#include <string>
#include <cmath>

#include "../common.h"

inline std::string split_string(pll_split_t split) {
	std::string binary = std::bitset<20>(*split).to_string();
	return binary;
}

class VpTree {
public:
	VpTree() :
			_split_len(0), _splits(0), _inv_splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _root(0) {
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

		_bs_light.resize(num_splits);
		// precompute lightside size for all bootstrap splits
		for (unsigned int j = 0; j < num_splits; j++) {
			_bs_light[j] = pllmod_utree_split_lightside(splits[j], nTax);
		}

		_items.resize(num_splits);
		for (size_t i = 0; i < num_splits; ++i) {
			_items[i] = i;
		}
		_root = buildFromPoints(0, _items.size());
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		_tau = std::numeric_limits<unsigned int>::max();
		search(_root, target, p);
		return std::min(_tau, p - 1);
		/*size_t min_idx = 0;
		 unsigned int min = std::numeric_limits<unsigned int>::max();
		 for (size_t i = 0; i < _items.size(); ++i) {
		 unsigned int dist = distance(target, _splits[i], _split_len);
		 if (dist < min) {
		 min = dist;
		 min_idx = i;
		 }
		 }
		 //std::cout << "   Sarah " << min << " for witness: " << split_string(_splits[min_idx]) << " and query: " << split_string(target) << "\n";
		 return min;*/
	}

private:
	unsigned int _split_len;
	pll_split_t * _splits;
	pll_split_t * _inv_splits;
	std::vector<unsigned int> _bs_light;
	std::vector<unsigned int> _items;
	unsigned int _tau;
	unsigned int _nTax;

	/* This function computes a lower bound of Hamming distance between splits:
	 * the computation terminates as soon as current distance values exceeds min_hdist.
	 * This allows for substantial time savings if we are looking for the
	 * minimum Hamming distance (as in TBE computation below).
	 *
	 * WARNING: This function does not check that hdist < N/2. Therefore,
	 * it should be called twice, with original and inverted s1 (or s2),
	 * to account for possible complementary split encoding.
	 * */
	static unsigned int split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int split_len,
			unsigned int max_interesting_dist) {
		unsigned int hdist = 0;
		unsigned int i;

		for (i = 0; (i < split_len) && (hdist <= max_interesting_dist); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}

		return hdist;
	}

	static unsigned int split_hamming_distance(pll_split_t s1, pll_split_t s2, unsigned int split_len) {
		unsigned int hdist = 0;
		unsigned int i;

		for (i = 0; (i < split_len); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}

		return hdist;
	}

	static unsigned int distance(pll_split_t s1, pll_split_t s1_inv, pll_split_t s2, unsigned int split_len, unsigned int nTax,
			unsigned int max_interesting_dist) {
		unsigned int dist = split_hamming_distance_lbound(s1, s2, split_len, max_interesting_dist);

		if (dist <= nTax / 2 && dist < max_interesting_dist) {
			return dist;
		}

		unsigned int dist_inv = split_hamming_distance_lbound(s1_inv, s2, split_len, max_interesting_dist);
		return std::min(dist, dist_inv);
	}

	static unsigned int distance(pll_split_t s1, pll_split_t s2, unsigned int split_len, unsigned int nTax) {
		unsigned int dist = split_hamming_distance(s1, s2, split_len);
		return std::min(dist, nTax - dist);
	}

	struct Node {
		int index;
		double threshold;
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

	Node* buildFromPoints(unsigned int lower, unsigned int upper) {
		if (upper == lower) {
			return NULL;
		}

		Node* node = new Node();
		node->index = lower;

		if (upper - lower > 1) {
			// choose an arbitrary point and move it to the start
			unsigned int i = upper - 1;
			//unsigned int i = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			std::swap(_items[lower], _items[i]);

			unsigned int median = (upper + lower) / 2;
			// what was the median?
			node->threshold = distance(_splits[_items[lower]], _splits[_items[median]], _split_len, _nTax);

			// partition around the median distance
			unsigned int medianDistance = node->threshold;
			unsigned int actEnd = upper - 1;
			for (size_t i = lower + 1; i < upper; ++i) {
				if (i == median) {
					continue;
				}
				if (i >= actEnd) {
					break;
				}

				unsigned int minDist;
				if (_bs_light[_items[i]] >= _bs_light[_items[median]]) {
					minDist = _bs_light[_items[i]] - _bs_light[_items[median]];
				} else {
					minDist = _bs_light[_items[median]] - _bs_light[_items[i]];
				}
				minDist = std::min(minDist, _nTax - minDist);

				unsigned int actDist;
				if (minDist > medianDistance) {
					actDist = minDist;
				} else {
					actDist = distance(_splits[_items[i]], _inv_splits[_items[i]], _splits[_items[median]], _split_len, _nTax,
							medianDistance + 1);
				}

				if (actDist > medianDistance && i < median) { // the element is on the wrong side, move it to the end
					unsigned int temp = _items[i];
					_items[i] = _items[actEnd];
					_items[actEnd] = temp;
					actEnd--;
				}
			}

			node->index = lower;
			node->left = buildFromPoints(lower + 1, median);
			node->right = buildFromPoints(median, upper);
		}

		return node;
	}

	void search(Node* node, pll_split_t target, unsigned int p) {
		if (node == NULL)
			return;

		if (_tau == 1) {
			return;
		}

		unsigned int minDist;
		if (p >= _bs_light[_items[node->index]]) {
			minDist = p - _bs_light[_items[node->index]];
		} else {
			minDist = _bs_light[_items[node->index]] - p;
		}
		minDist = std::min(minDist, _nTax - minDist);

		if (minDist >= node->threshold) { // dist >= minDist >= node->threshold ---> dist >= node->threshold
			bool distComputed = false;
			unsigned int dist;

			if (minDist < _tau) {
				unsigned int maxInterestingDist = node->threshold + _tau + 1;
				if (node->left == NULL && node->right == NULL) {
					maxInterestingDist = _tau;
				}
				dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
						maxInterestingDist);
				distComputed = true;
				if (dist < _tau) {
					_tau = dist;
				}
			}

			if (node->left == NULL && node->right == NULL) {
				return;
			}

			if (minDist + _tau >= node->threshold) {
				search(node->right, target, p);
			}

			if (minDist <= node->threshold + _tau && node->left != NULL) {
				if (!distComputed) {
					unsigned int maxInterestingDist = node->threshold + _tau + 1;
					dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
							maxInterestingDist); // do we need the dist computation here?
				}
				if (dist <= node->threshold + _tau) {
					search(node->left, target, p);
				}
			}
			return;
		}

		if (node->left == NULL && node->right == NULL) {
			unsigned int maxInterestingDist = _tau;
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
					maxInterestingDist);
			if (dist < _tau) {
				_tau = dist;
			}
			return;
		}

		if (node->left == NULL) {
			unsigned int maxInterestingDist = node->threshold;
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
					maxInterestingDist);
			if (dist < _tau) {
				_tau = dist;
			}
			if (dist < node->threshold) {
				if (dist + _tau >= node->threshold) {
					search(node->right, target, p);
				}

			}
			return;
		}

		if (node->right == NULL) {
			unsigned int maxInterestingDist;
			if (node->threshold >= _tau) {
				maxInterestingDist = node->threshold;
			} else {
				maxInterestingDist = _tau;
			}
			unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
					maxInterestingDist);
			if (dist < _tau) {
				_tau = dist;
			}

			if (dist < node->threshold) {
				search(node->left, target, p);
			}
			return;
		}

		unsigned int maxInterestingDist = node->threshold + _tau + 1;
		unsigned int dist = distance(_splits[_items[node->index]], _inv_splits[_items[node->index]], target, _split_len, _nTax,
				maxInterestingDist);
		if (dist < _tau) {
			_tau = dist;
		}

		if (dist < node->threshold) {
			if (dist <= node->threshold + _tau) {
				search(node->left, target, p);
			}

			if (dist + _tau >= node->threshold) {
				search(node->right, target, p);
			}

		}
	}
};

#endif /* SRC_BOOTSTRAP_VPTREE_HPP_ */
