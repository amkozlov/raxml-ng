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

#include "../common.h"

inline std::string split_string(pll_split_t split) {
	std::string binary = std::bitset<20>(*split).to_string();
	return binary;
}

class VpTree {
public:
	VpTree() :
			_split_len(0), _splits(0), _tau(std::numeric_limits<unsigned int>::max()), _nTax(0), _root(0) {
	}

	~VpTree() {
		delete _root;
	}

	void create(pll_split_t * splits, size_t split_len, size_t num_splits, size_t nTax) {
		delete _root;
		_split_len = split_len;
		_splits = splits;
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

	void search(pll_split_t target, int k, std::vector<unsigned int>* results, std::vector<double>* distances) {
		std::priority_queue<HeapItem> heap;

		_tau = std::numeric_limits<unsigned int>::max();
		search(_root, target, k, heap);

		results->clear();
		distances->clear();

		while (!heap.empty()) {
			results->push_back(_items[heap.top().index]);
			distances->push_back(heap.top().dist);
			heap.pop();
		}

		std::reverse(results->begin(), results->end());
		std::reverse(distances->begin(), distances->end());
	}

	unsigned int search_mindist(pll_split_t target, unsigned int p) {
		std::priority_queue<HeapItem> heap;

		_tau = std::numeric_limits<unsigned int>::max();
		search(_root, target, 1, heap);

		return std::min(heap.top().dist, p - 1);

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
	static unsigned int split_hamming_distance_lbound(pll_split_t s1, pll_split_t s2, unsigned int split_len, unsigned int min_hdist) {
		unsigned int hdist = 0;
		unsigned int i;

		for (i = 0; (i < split_len) && (hdist <= min_hdist); ++i) {
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

	static unsigned int distance(pll_split_t s1, pll_split_t s2, unsigned int split_len, unsigned int min_hdist, unsigned int nTax) {
		unsigned int dist = split_hamming_distance_lbound(s1, s2, split_len, min_hdist);
		return std::min(dist, nTax - dist);
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

	struct HeapItem {
		HeapItem(int index, unsigned int dist) :
				index(index), dist(dist) {
		}
		int index;
		unsigned int dist;
		bool operator<(const HeapItem& o) const {
			return dist < o.dist;
		}
	};

	struct DistanceComparator {
		const pll_split_t item;
		unsigned int _split_len;
		pll_split_t* _splits;
		unsigned int _nTax;
		DistanceComparator(pll_split_t item, unsigned int split_len, pll_split_t * splits, unsigned int nTax) :
				item(item), _split_len(split_len), _splits(splits), _nTax(nTax) {
		}
		bool operator()(const unsigned int& a, const unsigned int& b) {
			return distance(item, _splits[a], _split_len, _nTax) < distance(item, _splits[b], _split_len, _nTax);
		}
	};

	Node* buildFromPoints(int lower, int upper) {
		if (upper == lower) {
			return NULL;
		}

		Node* node = new Node();
		node->index = lower;

		if (upper - lower > 1) {

			// choose an arbitrary point and move it to the start
			int i = (int) ((double) rand() / RAND_MAX * (upper - lower - 1)) + lower;
			std::swap(_items[lower], _items[i]);

			int median = (upper + lower) / 2;

			// partition around the median distance
			std::nth_element(_items.begin() + lower + 1, _items.begin() + median, _items.begin() + upper,
					DistanceComparator(_splits[_items[lower]], _split_len, _splits, _nTax));

			// what was the median?
			node->threshold = distance(_splits[_items[lower]], _splits[_items[median]], _split_len, _nTax);

			node->index = lower;
			node->left = buildFromPoints(lower + 1, median);
			node->right = buildFromPoints(median, upper);
		}

		return node;
	}

	void search(Node* node, pll_split_t target, unsigned int k, std::priority_queue<HeapItem>& heap) {
		if (node == NULL)
			return;

		double dist = distance(_splits[_items[node->index]], target, _split_len, _nTax);
		//printf("dist=%g tau=%gn", dist, _tau );

		if (dist < _tau) {
			if (heap.size() == k)
				heap.pop();
			heap.push(HeapItem(node->index, dist));
			if (heap.size() == k)
				_tau = heap.top().dist;
		}

		if (node->left == NULL && node->right == NULL) {
			return;
		}

		if (dist < node->threshold) {
			if (dist - _tau <= node->threshold) {
				search(node->left, target, k, heap);
			}

			if (dist + _tau >= node->threshold) {
				search(node->right, target, k, heap);
			}

		} else {
			if (dist + _tau >= node->threshold) {
				search(node->right, target, k, heap);
			}

			if (dist - _tau <= node->threshold) {
				search(node->left, target, k, heap);
			}
		}
	}
};

#endif /* SRC_BOOTSTRAP_VPTREE_HPP_ */
