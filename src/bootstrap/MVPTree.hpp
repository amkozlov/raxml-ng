/*
 * VPTree.hpp
 *
 *  Created on: Jan 15, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_MVPTREE_HPP_
#define SRC_BOOTSTRAP_MVPTREE_HPP_

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

class MvpTree {
public:
	static const unsigned int BUCKET_SIZE = 100; // This is the k parameter
	static const unsigned int LOOK_BACK = 2; // This is the p parameter

	MvpTree() :
			_split_len(0), _splits(0), _inv_splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _nTax_div_2(0), _root(0) {
	}

	~MvpTree() {
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
		_path.resize(num_splits);
		for (size_t i = 0; i < _path.size(); ++i) {
			_path[i].resize(LOOK_BACK + 1); // because this array is currently 1-indexexed.
		}
		_root = buildFromPoints(0, _items.size(), dist_to_lower, 1);
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		_tau = p - 1;
		//std::cout << "tau start: " << _tau << " ; n/2: " << _nTax_div_2 << "\n";
		std::vector<unsigned int> searchPath(LOOK_BACK + 1);
		//search(_root, target, p, 1, searchPath);
		search_dumb(_root, target, p, 1, searchPath);

		// check if the result is correct
		size_t min_idx = 0;
		unsigned int min = p - 1;
		for (size_t i = 0; i < _items.size(); ++i) {
			unsigned int dist = distance(target, _splits[i]);
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
			throw std::runtime_error("Stopping now");
		}

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
	std::vector<std::vector<unsigned int> > _path;

	/* This function computes a lower bound of Hamming distance between splits:
	 * the computation terminates as soon as current distance values exceeds min_hdist.
	 * This allows for substantial time savings if we are looking for the
	 * minimum Hamming distance (as in TBE computation below).
	 *
	 * WARNING: This function does not check that hdist < N/2. Therefore,
	 * it should be called twice, with original and inverted s1 (or s2),
	 * to account for possible complementary split encoding.
	 * */
	inline unsigned int split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int min_hdist) {
		unsigned int hdist = 0;
		unsigned int i;
		for (i = 0; (i < _split_len) && (hdist <= min_hdist); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}
		return hdist;
	}

	inline void split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int min_hdist, unsigned int& hdist,
			unsigned int& i) {
		for (; (i < _split_len) && (hdist <= min_hdist); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}
	}

	inline unsigned int split_hamming_distance(pll_split_t s1, pll_split_t s2) {
		unsigned int hdist = 0;
		unsigned int i;
		for (i = 0; (i < _split_len); ++i) {
			hdist += PLL_POPCNT32(s1[i] ^ s2[i]);
		}
		return hdist;
	}

	inline unsigned int distance(pll_split_t s1, pll_split_t s1_inv, pll_split_t s2, unsigned int max_interesting_distance) {
		unsigned int dist = split_hamming_distance_lbound(s1, s2, max_interesting_distance);
		if (dist < max_interesting_distance) {
			return dist;
		}
		unsigned int dist_inv = split_hamming_distance_lbound(s1_inv, s2, max_interesting_distance);
		return std::min(dist, dist_inv);
	}

	inline unsigned int distance(pll_split_t s1, pll_split_t s1_inv, pll_split_t s2, unsigned int max_interesting_distance,
			unsigned int &old_dist_forward, unsigned int& old_dist_reverse, unsigned int& old_i_forward, unsigned int& old_i_reverse,
			unsigned int minDist) {
		if (minDist > max_interesting_distance || std::min(old_dist_forward, old_dist_reverse) > max_interesting_distance) {
			return max_interesting_distance + 1;
		}
		split_hamming_distance_lbound(s1, s2, max_interesting_distance, old_dist_forward, old_i_forward);
		if (old_dist_forward < max_interesting_distance) {
			return old_dist_forward;
		}
		split_hamming_distance_lbound(s1_inv, s2, max_interesting_distance, old_dist_reverse, old_i_reverse);
		return std::min(old_dist_forward, old_dist_reverse);
	}

	inline unsigned int distance(pll_split_t s1, pll_split_t s2) {
		unsigned int dist = split_hamming_distance(s1, s2);
		return std::min(dist, _nTax - dist);
	}

	typedef struct LeafInformation {
		unsigned int index;
		unsigned int distFirstVP;
		unsigned int distSecondVP;
	} LeafInformation;

	struct Node {
		std::vector<LeafInformation> leafData;
		unsigned int indexVP1;
		unsigned int indexVP2;
		// median distances:
		unsigned int m1;
		unsigned int m2_1;
		unsigned int m2_2;
		Node* left1;
		Node* left2;
		Node* right1;
		Node* right2;
		Node() :
				indexVP1(0), indexVP2(0), m1(0), m2_1(0), m2_2(0), left1(0), left2(0), right1(0), right2(0) {
		}
		~Node() {
			delete left1;
			delete left2;
			delete right1;
			delete right2;
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

	unsigned int findVantagePoint(unsigned int lower, unsigned int upper) {
		// chose a random node
		unsigned int cand = (unsigned int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
		// find the node that is farthest away from this node as VP point
		unsigned int maxDist = 0;
		unsigned int vpPoint = lower;

		static const unsigned int NUM_SAMPLES = 200;
		static const unsigned int MAX_COLLISIONS = 5;
		std::unordered_set<unsigned int> samples;
		unsigned int actCollisions = 0;
		while (samples.size() < (upper - lower - 1) && samples.size() < NUM_SAMPLES) {
			// try to randomly pick a sample
			unsigned int sam = (unsigned int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			if (sam != cand) {
				if (samples.find(sam) != samples.end()) {
					actCollisions++;
					if (actCollisions >= MAX_COLLISIONS) {
						break;
					}
				}
				samples.insert(sam);
			}
		}

		for (unsigned int i : samples) {
			unsigned int dist = distance(_splits[_items[cand]], _inv_splits[_items[cand]], _splits[_items[i]], _nTax_div_2);
			if (dist > maxDist) {
				maxDist = dist;
				vpPoint = i;
			}
		}
		return vpPoint;
	}

	Node* buildFromPoints(unsigned int lower, unsigned int upper, std::vector<unsigned int>& dist_to_lower, unsigned int level) {
		if (upper == lower) {
			return NULL;
		}

		Node* node = new Node();
		if (upper - lower <= BUCKET_SIZE + 2) { // Create a leaf node.
		// choose an arbitrary point and move it to the start
			unsigned int vp1 = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			node->indexVP1 = _items[vp1];
			node->leafData.resize(upper - lower);
			unsigned int maxDist = 0;
			unsigned int maxDistIdx = 0;
			for (size_t i = 0; i < node->leafData.size(); ++i) {
				node->leafData[i].index = _items[lower + i];
				if (node->leafData[i].index == node->indexVP1) {
					node->leafData[i].distFirstVP = 0;
				} else {
					unsigned int dist = distance(_splits[_items[node->indexVP1]], _inv_splits[_items[node->indexVP1]],
							_splits[_items[node->leafData[i].index]], _nTax_div_2);
					if (dist > maxDist) {
						maxDist = dist;
						maxDistIdx = node->leafData[i].index;
					}
					node->leafData[i].distFirstVP = dist;
				}
			}
			node->indexVP2 = maxDistIdx;
			for (size_t i = 0; i < node->leafData.size(); ++i) {
				if (node->leafData[i].index == node->indexVP1) {
					continue;
				} else if (node->leafData[i].index == node->indexVP2) {
					node->leafData[i].distSecondVP = 0;
				} else {
					unsigned int dist = distance(_splits[_items[node->indexVP2]], _inv_splits[_items[node->indexVP2]],
							_splits[_items[node->leafData[i].index]], _nTax_div_2);
					node->leafData[i].distSecondVP = dist;
				}
			}
		} else { // Create an inner node.
			// choose an arbitrary point and move it to the start
			unsigned int vp1 = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			std::swap(_items[lower], _items[vp1]);
			node->indexVP1 = _items[lower];

			// precompute dist_to_lower once
			for (size_t i = lower + 1; i < upper; ++i) {
				unsigned int dist = distance(_splits[_items[lower]], _inv_splits[_items[lower]], _splits[_items[i]], _nTax_div_2);
				dist_to_lower[_items[i]] = dist;
				if (level <= LOOK_BACK) {
					_path[_items[i]][level] = dist;
				}
			}
			unsigned int median = (upper + lower) / 2;
			// partition around the median distance
			std::nth_element(_items.begin() + lower + 1, _items.begin() + median, _items.begin() + upper,
					DistanceComparator(dist_to_lower));
			// what was the median?
			node->m1 = dist_to_lower[_items[median]];
			// now, SS1 = [lower + 1, median) and SS2 = [median, upper)

			std::cout << "distances to VP 1:\n";
			for (size_t i = lower + 1; i < upper; ++i) {
				if (i == median) {
					std::cout << "*" << dist_to_lower[_items[i]] << "* ";
				} else {
					std::cout << dist_to_lower[_items[i]] << " ";
				}
			}
			std::cout << "\n";

			// select second vantage point from SS2 and move it to lower + 1.
			unsigned int vp2 = (int) ((double) rand() / RAND_MAX * (upper - median - 1)) + median;
			std::swap(_items[lower + 1], _items[vp2]);
			node->indexVP2 = _items[lower + 1];
			// calculate distances to second vantage point, reusing the array from before.
			for (size_t i = lower + 2; i < upper; ++i) {
				unsigned int dist = distance(_splits[_items[lower + 1]], _inv_splits[_items[lower + 1]], _splits[_items[i]], _nTax_div_2);
				dist_to_lower[_items[i]] = dist;
				if (level < LOOK_BACK) {
					_path[_items[i]][level + 1] = dist;
				}
			}
			// now SS1 = [lower + 2, median) and SS2 = [median, upper).

			unsigned int lowerSS1 = lower + 2;
			unsigned int upperSS1 = median;
			unsigned int median2_1 = (upperSS1 + lowerSS1) / 2;
			// partition SS1 around the median distance
			std::nth_element(_items.begin() + lowerSS1, _items.begin() + median2_1, _items.begin() + upperSS1,
					DistanceComparator(dist_to_lower));
			node->m2_1 = dist_to_lower[_items[median2_1]];

			unsigned int lowerSS2 = median;
			unsigned int upperSS2 = upper;
			unsigned int median2_2 = (upperSS2 + lowerSS2) / 2;
			// partition SS2 around the median distance
			std::nth_element(_items.begin() + lowerSS2, _items.begin() + median2_2, _items.begin() + upperSS2,
					DistanceComparator(dist_to_lower));
			node->m2_2 = dist_to_lower[_items[median2_2]];

			std::cout << "distances to VP 2 in SS1:\n";
			for (size_t i = lowerSS1; i < upperSS1; ++i) {
				if (i == median2_1) {
					std::cout << "*" << dist_to_lower[_items[i]] << "* ";
				} else {
					std::cout << dist_to_lower[_items[i]] << " ";
				}
			}
			std::cout << "\n";

			std::cout << "distances to VP 2 in SS2:\n";
			for (size_t i = lowerSS2; i < upperSS2; ++i) {
				if (i == median2_2) {
					std::cout << "*" << dist_to_lower[_items[i]] << "* ";
				} else {
					std::cout << dist_to_lower[_items[i]] << " ";
				}
			}
			std::cout << "\n";

			level += 2;

			node->left1 = buildFromPoints(lowerSS1, median2_1, dist_to_lower, level);
			node->left2 = buildFromPoints(median2_1, upperSS1, dist_to_lower, level);
			node->right1 = buildFromPoints(lowerSS2, median2_2, dist_to_lower, level);
			node->right2 = buildFromPoints(median2_2, upperSS2, dist_to_lower, level);
		}
		return node;
	}

	void search_dumb(Node* node, pll_split_t target, unsigned int p, unsigned int level, std::vector<unsigned int>& searchPath) {
		//std::cout << "search called\n";
		if (node == NULL || _tau == 1) {
			return;
		}
		unsigned int dVP1 = distance(_splits[node->indexVP1], _inv_splits[node->indexVP1], target, _nTax_div_2);
		unsigned int dVP2 = distance(_splits[node->indexVP2], _inv_splits[node->indexVP2], target, _nTax_div_2);
		_tau = std::min(_tau, dVP1);
		_tau = std::min(_tau, dVP2);
		if (!node->leafData.empty()) { // current node is a leaf node
			for (size_t i = 0; i < node->leafData.size(); ++i) {
				unsigned int dist = distance(_splits[node->leafData[i].index], _inv_splits[node->leafData[i].index], target, _tau);
				_tau = std::min(_tau, dist);
			}
		} else { // current node is an internal node
			if (dVP1 <= _tau + node->m1) {
				search_dumb(node->left1, target, p, level + 2, searchPath);
				search_dumb(node->left2, target, p, level + 2, searchPath);
			}
			if (dVP2 + _tau >= node->m1) {
				search_dumb(node->right1, target, p, level + 2, searchPath);
				search_dumb(node->right2, target, p, level + 2, searchPath);
			}
		}
	}

	void search(Node* node, pll_split_t target, unsigned int p, unsigned int level, std::vector<unsigned int>& searchPath) {
		if (node == NULL || _tau == 1) {
			return;
		}
		unsigned int dVP1 = distance(_splits[node->indexVP1], _inv_splits[node->indexVP1], target, _nTax_div_2);
		unsigned int dVP2 = distance(_splits[node->indexVP2], _inv_splits[node->indexVP2], target, _nTax_div_2);
		_tau = std::min(_tau, dVP1);
		_tau = std::min(_tau, dVP2);
		if (!node->leafData.empty()) { // current node is a leaf node
			for (size_t i = 0; i < node->leafData.size(); ++i) {
				unsigned int d1 = node->leafData[i].distFirstVP;
				unsigned int d2 = node->leafData[i].distSecondVP;
				if ((dVP1 <= d1 + _tau && d1 <= dVP1 + _tau) && (dVP2 <= d2 + _tau && d2 <= dVP2 + _tau)) {
					bool condHolds = true;
					for (size_t j = 1; j <= LOOK_BACK; ++j) {
						if ((searchPath[j] > _path[node->leafData[i].index][j] + _tau)
								|| (searchPath[j] + _tau < _path[node->leafData[i].index][j])) {
							condHolds = false;
							break;
						}
					}
					if (condHolds) {
						unsigned int actMinDist;
						if (p >= _bs_light[_items[node->leafData[i].index]]) {
							actMinDist = p - _bs_light[_items[node->leafData[i].index]];
						} else {
							actMinDist = _bs_light[_items[node->leafData[i].index]] - p;
						}
						if (actMinDist < _tau) {
							unsigned int dist = distance(_splits[node->leafData[i].index], _inv_splits[node->leafData[i].index], target,
									_tau);
							_tau = std::min(_tau, dist);
						}
					}
				}
			}
		} else { // current node is an internal node
			if (level <= LOOK_BACK) {
				searchPath[level] = dVP1;
				if (level < LOOK_BACK) {
					searchPath[level + 1] = dVP2;
				}
			}
			if (dVP1 + _tau <= node->m1) {
				if (dVP2 + _tau <= node->m2_1) {
					// recursively search the first branch with level = level + 2
					search(node->left1, target, p, level + 2, searchPath);
				}
				if (dVP2 >= node->m2_1 + _tau) {
					// recursively search the second branch with level = level + 2
					search(node->left2, target, p, level + 2, searchPath);
				}
			}
			if (dVP1 >= node->m1 + _tau) {
				if (dVP2 + _tau <= node->m2_2) {
					// recursively search the third branch with level = level + 2
					search(node->right1, target, p, level + 2, searchPath);
				}
				if (dVP2 >= node->m2_2 + _tau) {
					// recursively search the fourth branch with level = level + 2
					search(node->right2, target, p, level + 2, searchPath);
				}
			}
		}
	}
};

#endif /* SRC_BOOTSTRAP_MVPTREE_HPP_ */
