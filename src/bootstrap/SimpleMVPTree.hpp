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
 * TODO: Add the directory node back. It splits the items in NUM_VANTAGE_POINTS^2 directories.
 */

class SimpleMvpTree {
public:
	static const unsigned int NUM_VANTAGE_POINTS = 7;

	SimpleMvpTree() :
			_split_len(0), _splits(0), _inv_splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _nTax_div_2(0), _root(NULL) {
	}

	~SimpleMvpTree() {
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
		_vp_indices.resize(NUM_VANTAGE_POINTS);
		_distToVP.resize(num_splits);

		_root = buildFromPoints(0, _items.size());
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		_tau = p - 1;

		/*std::vector<unsigned int> vp_min_dist(NUM_VANTAGE_POINTS);
		 for (size_t i = 0; i < NUM_VANTAGE_POINTS; ++i) {
		 if (p >= _bs_light[_vp_indices[i]]) {
		 vp_min_dist[i] = p - _bs_light[_vp_indices[i]];
		 } else {
		 vp_min_dist[i] = _bs_light[_vp_indices[i]] - p;
		 }
		 }*/

		std::vector<unsigned int> vp_dist(NUM_VANTAGE_POINTS);
		for (size_t i = 0; i < NUM_VANTAGE_POINTS; ++i) {
			vp_dist[i] = distance(_splits[_vp_indices[i]], _inv_splits[_vp_indices[i]], target, _nTax_div_2);
			_tau = std::min(_tau, vp_dist[i]);
			if (_tau == 1) {
				return 1;
			}
		}
		search(_root, target, p, vp_dist, 0);

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
	std::vector<unsigned int> _vp_indices;
	std::vector<std::array<unsigned int, NUM_VANTAGE_POINTS> > _distToVP;

	typedef struct DirectoryNode {
		DirectoryNode* left;
		DirectoryNode* right;
		unsigned int s1, e1;
		unsigned int s2, e2;
		unsigned int threshold; // median distance
	} DirectoryNode;

	DirectoryNode* _root;

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
		const std::vector<std::array<unsigned int, NUM_VANTAGE_POINTS> >& _distToVP;
		unsigned int _vpIdx;

		DistanceComparator(const std::vector<std::array<unsigned int, NUM_VANTAGE_POINTS> >& distToVP, unsigned int vpIdx) :
				_distToVP(distToVP), _vpIdx(vpIdx) {
		}
		bool operator()(const unsigned int& a, const unsigned int& b) {
			return _distToVP[a][_vpIdx] < _distToVP[b][_vpIdx];
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

	DirectoryNode* makeDirectory(unsigned int lower, unsigned int upper, unsigned int actVPIndex) {
		DirectoryNode* node = new DirectoryNode();
		if (lower >= upper) {
			return node;
		}

		unsigned int median = (upper + lower) / 2;
		// partition around the median distance from second VP, part 1
		std::nth_element(_items.begin() + lower, _items.begin() + median, _items.begin() + upper,
				DistanceComparator(_distToVP, actVPIndex));
		node->s1 = lower;
		node->e1 = median;
		node->s2 = median;
		node->e2 = upper;
		node->threshold = _distToVP[_items[median]][actVPIndex];

		if (actVPIndex < NUM_VANTAGE_POINTS - 1) {
			node->left = makeDirectory(node->s1, node->e1, actVPIndex + 1);
			node->right = makeDirectory(node->s2, node->e2, actVPIndex + 1);
		}

		return node;
	}

	DirectoryNode* buildFromPoints(unsigned int lower, unsigned int upper) {
		DirectoryNode* root = new DirectoryNode();
		if (upper == lower) {
			return root;
		}
		unsigned int actVPIndex = 0;

		unsigned int maxDist = 0;
		unsigned int maxDistIdx = 0;
		// first Vantage point is a bit different from the rest:
		unsigned int vp = findVantagePoint(0, upper);
		_vp_indices[0] = _items[vp];
		std::swap(_items[lower + 0], _items[vp]);
		for (size_t j = lower + 0 + 1; j < upper; ++j) {
			unsigned int dist = distance(_splits[_items[j]], _inv_splits[_items[j]], _splits[_items[lower + 0]], _nTax_div_2);
			_distToVP[_items[j]][0] = dist;
			if (dist > maxDist) {
				maxDist = dist;
				maxDistIdx = _items[j];
			}
		}

		for (size_t i = 1; i < NUM_VANTAGE_POINTS; ++i) {
			unsigned int vp = maxDistIdx;
			_vp_indices[i] = _items[vp];
			std::swap(_items[lower + i], _items[vp]);
			maxDist = 0;
			maxDistIdx = 0;
			for (size_t j = lower + i + 1; j < upper; ++j) {
				unsigned int dist = distance(_splits[_items[j]], _inv_splits[_items[j]], _splits[_items[lower + i]], _nTax_div_2);
				_distToVP[_items[j]][i] = dist;
				// look at the minimum distance from vantage points so far
				for (size_t k = 1; k < i; ++k) {
					dist = std::min(dist, _distToVP[_items[j]][k]);
				}
				if (dist > maxDist) {
					maxDist = dist;
					maxDistIdx = _items[j];
				}
			}
		}

		/*
		 // choose all VP_points at once, always move them to the start.
		 for (size_t i = 0; i < NUM_VANTAGE_POINTS; ++i) {
		 unsigned int vp = findVantagePoint2(i, upper, 0);
		 _vp_indices[i] = _items[vp];
		 std::swap(_items[lower + i], _items[vp]);
		 }
		 // precompute distances to the vantage points
		 for (size_t i = NUM_VANTAGE_POINTS; i < upper; ++i) {
		 for (size_t j = 0; j < NUM_VANTAGE_POINTS; ++j) {
		 unsigned int dist = distance(_splits[_items[lower + j]], _inv_splits[_items[lower + j]], _splits[_items[i]], _nTax_div_2);
		 _distToVP[_items[i]][j] = dist;
		 }
		 }
		 */
		// reorder the items and store it in the directory.
		unsigned int median = (upper + lower + NUM_VANTAGE_POINTS) / 2;
		// partition around the median distance from first VP
		std::nth_element(_items.begin() + lower + NUM_VANTAGE_POINTS, _items.begin() + median, _items.begin() + upper,
				DistanceComparator(_distToVP, actVPIndex));
		root->s1 = lower + NUM_VANTAGE_POINTS;
		root->e1 = median;
		root->s2 = median;
		root->e2 = upper;
		root->threshold = _distToVP[_items[median]][actVPIndex];

		if (actVPIndex < NUM_VANTAGE_POINTS - 1) {
			root->left = makeDirectory(root->s1, root->e1, actVPIndex + 1);
			root->right = makeDirectory(root->s2, root->e2, actVPIndex + 1);
		}
		return root;
	}

	void iterate(pll_split_t target, unsigned int p, const std::vector<unsigned int>& vp_dist, unsigned int lower, unsigned int upper) {
		for (size_t i = lower; i < upper; ++i) {
			bool okay = true;
			for (size_t j = 0; j < NUM_VANTAGE_POINTS; ++j) {
				if ((vp_dist[j] > _distToVP[_items[i]][j] + _tau) || (_distToVP[_items[i]][j] > vp_dist[j] + _tau)) {
					okay = false;
					break;
				}
			}
			if (okay) {
				unsigned int actMinDist;
				if (p >= _bs_light[_items[i]]) {
					actMinDist = p - _bs_light[_items[i]];
				} else {
					actMinDist = _bs_light[_items[i]] - p;
				}
				if (actMinDist < _tau) {
					unsigned int dist = distance(_splits[_items[i]], _inv_splits[_items[i]], target, _tau);
					_tau = std::min(_tau, dist);
					if (_tau == 1) {
						return;
					}
				}
			}
		}
	}

	void search(DirectoryNode* node, pll_split_t target, unsigned int p, const std::vector<unsigned int>& vp_dist, unsigned int actVPIdx) {
		if (node == NULL) {
			return;
		}
		if (actVPIdx == NUM_VANTAGE_POINTS - 1) {
			if (vp_dist[actVPIdx] <= node->threshold + _tau) { // search in left side
				iterate(target, p, vp_dist, node->s1, node->e1);
			}
			if (vp_dist[actVPIdx] + _tau >= node->threshold) { // search in right side
				iterate(target, p, vp_dist, node->s2, node->e2);
			}
		} else { // more search in directory structure
			if (vp_dist[actVPIdx] <= node->threshold + _tau) { // search in left side
				search(node->left, target, p, vp_dist, actVPIdx + 1);
			}
			if (vp_dist[actVPIdx] + _tau >= node->threshold) { // search in right side
				search(node->right, target, p, vp_dist, actVPIdx + 1);
			}
		}
	}
};

#endif /* SRC_BOOTSTRAP_SIMPLEMVPTREE_HPP_ */
