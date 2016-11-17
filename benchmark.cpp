#include <float.h>
#include <stdint.h>
#include <stdio.h>

#include "make-float.h"

int main(void) {
	unsigned count = 0;
	uint32_t n = 0;

	do {
		count += make_float(n & MAKE_FLOAT_MAX) < 0.1;
	} while (++n);

	printf("|n < 0.1| = %u\n", count);

	return 0;
}
