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


static void print_bar(unsigned width) {
	for (; width > 1; width -= 2) {
		putchar('#');
	}
	if (width) {
		putchar('.');
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
	static const unsigned size = 32;

	uint32_t buckets[size], out_of_range = 0, n;
	unsigned i;

	memset(buckets, 0, sizeof buckets);

	for (const auto &pair : list) {
		i = pair.second * size;
		if (i < size) {
			buckets[i] += pair.first;
		} else {
			out_of_range += pair.first;
		}
	}

	n = buckets[0];
	for (i = 1; i < size; ++i) {
		if (buckets[i] > n) {
			n = buckets[i];
		}
	}

	double width_ratio = 100.0 / n;
	double step = 1.0 / size;

	putchar('\n');
	for (i = 0; i < size; ++i) {
		n = buckets[i];
		printf("%5.3f [%9" PRIu32 "] ", i * step, n);
		print_bar(n * width_ratio);
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
