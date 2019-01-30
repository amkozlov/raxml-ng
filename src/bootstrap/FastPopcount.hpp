/*
 * FastPopcount.hpp
 *
 *  Created on: Jan 23, 2019
 *      Author: sarah
 */

#ifndef SRC_BOOTSTRAP_FASTPOPCOUNT_HPP_
#define SRC_BOOTSTRAP_FASTPOPCOUNT_HPP_

#include <cstdint>

static uint16_t wordbits[65536];
static bool wordbits_filled = false;

void popcount32e_init(void) {
	uint32_t i;
	uint16_t x;
	int count;
	for (i = 0; i <= 0xFFFF; i++) {
		x = i;
		for (count = 0; x; count++) // borrowed from popcount64d() above
			x &= x - 1;
		wordbits[i] = count;
	}
}

inline int popcount32e(uint32_t x) {
	return wordbits[x & 0xFFFF] + wordbits[x >> 16];
}

#endif /* SRC_BOOTSTRAP_FASTPOPCOUNT_HPP_ */
