/*
 * Benchmark of integer→real conversion methods.
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
