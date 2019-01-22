/*
 * VPTree.hpp
 *
 *  Created on: Jan 15, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_SIMPLEMVPTREE_HPP_
#define SRC_BOOTSTRAP_SIMPLEMVPTREE_HPP_

#include <bits/move.h>
#include <stddef.h>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>
#include <array>
#include <unordered_set>

#include "../../build/localdeps/include/libpll/pll.h"
#include "../../build/localdeps/include/libpll/pll_tree.h"

inline std::string split_string(pll_split_t split) {
	std::string binary = std::bitset<20>(*split).to_string();
	return binary;
}

/*
 * A very simple MVP tree. It consists of only a single node and a bunch of vantage points.
 */

class SimpleMvpTree {
public:
	static const unsigned int NUM_VANTAGE_POINTS = 2;

	SimpleMvpTree() :
			_split_len(0), _splits(0), _inv_splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _nTax_div_2(0) {
	}

	void create(pll_split_t * splits, pll_split_t * inv_splits, size_t split_len, size_t num_splits, size_t nTax) {
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
		_vp_indices.resize(NUM_VANTAGE_POINTS);
		std::vector<unsigned int> dist_to_lower(_items.size());
		buildFromPoints(0, _items.size(), dist_to_lower);
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		_tau = p - 1;
		search(target, p);

		/*
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
		 std::cout << "witness: " << split_string(_splits[min_idx]) << "\n";
		 throw std::runtime_error("Stopping now");
		 }*/

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

	typedef struct LeafInformation {
		unsigned int index;
		std::array<unsigned int, NUM_VANTAGE_POINTS> distToVP;
	} LeafInformation;

	std::vector<LeafInformation> _leafData;
	std::vector<unsigned int> _vp_indices;

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

	void buildFromPoints(unsigned int lower, unsigned int upper, std::vector<unsigned int>& dist_to_lower) {
		if (upper == lower) {
			return;
		}

		// Create a leaf node.
		// choose an arbitrary point and move it to the start
		unsigned int vp1 = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
		std::swap(_items[lower], _items[vp1]);
		_vp_indices[0] = _items[lower];
		_leafData.reserve(upper - lower);

		unsigned int maxDist = 0;
		unsigned int maxDistIdx = 0;
		// precompute dist to lower
		for (size_t i = lower + 1; i < upper; ++i) {
			unsigned int dist = distance(_splits[_items[lower]], _inv_splits[_items[lower]], _splits[_items[i]], _nTax_div_2);
			dist_to_lower[_items[i]] = dist;
			if (dist > maxDist) {
				maxDist = dist;
				maxDistIdx = i;
			}
		}
		std::swap(_items[lower + 1], _items[maxDistIdx]);
		_vp_indices[1] = _items[lower + 1];
		// create leaf data
		for (size_t i = lower + 2; i < upper; ++i) {
			LeafInformation info;
			info.index = _items[i];
			info.distToVP[0] = dist_to_lower[info.index];
			info.distToVP[1] = distance(_splits[_items[lower + 1]], _inv_splits[_items[lower + 1]], _splits[_items[i]], _nTax_div_2);
			_leafData.push_back(info);
		}
		_leafData.shrink_to_fit();
	}

	void search(pll_split_t target, unsigned int p) {
		std::vector<unsigned int> vp_min_dist(NUM_VANTAGE_POINTS);
		for (size_t i = 0; i < NUM_VANTAGE_POINTS; ++i) {
			if (p >= _bs_light[_vp_indices[i]]) {
				vp_min_dist[i] = p - _bs_light[_vp_indices[i]];
			} else {
				vp_min_dist[i] = _bs_light[_vp_indices[i]] - p;
			}
		}

		std::vector<unsigned int> vp_dist(NUM_VANTAGE_POINTS);
		for (size_t i = 0; i < NUM_VANTAGE_POINTS; ++i) {
			vp_dist[i] = distance(_splits[_vp_indices[i]], _inv_splits[_vp_indices[i]], target, _nTax_div_2);
			_tau = std::min(_tau, vp_dist[i]);
			if (_tau == 1) {
				return;
			}
		}

		for (size_t i = 0; i < _leafData.size(); ++i) {
			unsigned int d1 = _leafData[i].distToVP[0];
			unsigned int d2 = _leafData[i].distToVP[1];
			if ((vp_dist[0] <= d1 + _tau && d1 <= vp_dist[0] + _tau) && (vp_dist[1] <= d2 + _tau && d2 <= vp_dist[1] + _tau)) {
				unsigned int actMinDist;
				if (p >= _bs_light[_leafData[i].index]) {
					actMinDist = p - _bs_light[_leafData[i].index];
				} else {
					actMinDist = _bs_light[_leafData[i].index] - p;
				}
				if (actMinDist < _tau) {
					unsigned int dist = distance(_splits[_leafData[i].index], _inv_splits[_leafData[i].index], target, _tau);
					_tau = std::min(_tau, dist);
					if (_tau == 1) {
						return;
					}
				}
			}
		}
	}
};

#endif /* SRC_BOOTSTRAP_SIMPLEMVPTREE_HPP_ */
