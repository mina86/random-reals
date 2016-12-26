/*
 * Correctness test of integer→real conversion methods.
 * Copyright © 2016 by Michał Nazarewicz <mina86@mina86.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

/* See https://mina86.com/2016/random-reals/ for discussion. */

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "make-float.h"


typedef std::pair<unsigned, float> Pair;
typedef std::vector<Pair> List;


static List get_list() {
	std::unordered_map<float, unsigned> counts;
	for (uint32_t i = 0; i <= MAKE_FLOAT_MAX; ++i) {
		++counts[make_float(i)];
	}

	List list;
	list.reserve(counts.size());
	for (const auto &pair : counts) {
		list.emplace_back(pair.second, pair.first);
	}
	std::sort(list.begin(), list.end());

	return list;
}


static void print_bar(unsigned width, bool dots=false) {
	if (dots) {
		fputs("...", stdout);
	}
	for (; width > 1; width -= 2) {
		putchar('#');
	}
	if (width) {
		putchar('|');
	}
	putchar('\n');
}


template<class It>
static void print_pairs(It it, It end, uint32_t max) {
	double width_ratio = 80.0 / max;
	for (; it != end; ++it) {
		printf("%*.*g [%4" PRIu32 "] ",
		       DBL_DIG + 6, DBL_DIG, it->second,
		       it->first);
		print_bar(it->first * width_ratio);
	}
}


static void print_histogram(const List &list) {
	static const unsigned count = 32;

	uint32_t buckets[count], out_of_range = 0, n;
	unsigned i;

	memset(buckets, 0, sizeof buckets);

	for (const auto &pair : list) {
		i = pair.second * count;
		if (i < count) {
			buckets[i] += pair.first;
		} else {
			out_of_range += pair.first;
		}
	}

	uint32_t min = buckets[0], max = min;
	for (i = 1; i < count; ++i) {
		if (buckets[i] > max) {
			max = buckets[i];
		} else if (buckets[i] < min) {
			min = buckets[i];
		}
	}
	if (min == max) {
		min = 0;
	} else {
		uint32_t d = (max - min) / 2;
		if (min >= d) {
			min -= d;
		}
	}

	double width_ratio = (min ? 94.0 : 100.0) / (max - min);
	double step = 1.0 / count;

	putchar('\n');
	for (i = 0; i < count; ++i) {
		n = buckets[i];
		printf("%5.3f [%9" PRIu32 "] ", i * step, n);
		print_bar((n - min)* width_ratio, min);
	}

	if (out_of_range) {
		printf("\n!!! got %" PRIu32 " out of range values !!!\n",
		       out_of_range);
	}
}


int main(void) {
	List list = get_list();

	if (list.size() <= 23) {
		print_pairs(list.begin(), list.end(), list.back().first);
	} else {
		print_pairs(list.begin(), list.begin() + 10, list.back().first);
		puts("  .\n  .\n  .");
		print_pairs(list.end() - 10, list.end(), list.back().first);
	}

	print_histogram(list);

	return 0;
}
