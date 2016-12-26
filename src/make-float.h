/*
 * Implementation of some integer→real conversion methods.
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

#include <stdint.h>
#include <string.h>
#include <float.h>

#ifdef USE_BITS

#if !defined(__STDC_IEC_559__) || FLT_RADIX != 2 || FLT_MANT_DIG != 24
#  error "This code requires IEEE 754 floating point arithmetic."
#endif

#define MAKE_FLOAT_MAX ((UINT32_C(1) << 23) - 1U)

static inline float make_float(uint32_t n) {
	struct _ {
		char float_is_32_bit[sizeof(float) == sizeof n ? 1 : -1];
	};

	float ret;
	n = (n & ((1U << 23) - 1)) | (127 << 23);
	memcpy(&ret, &n, sizeof ret);
	return ret - 1.0f;
}

#else

#define MAKE_FLOAT_MAX ((UINT32_C(1) << 31) - 1U)

static inline float make_float(uint32_t n) {
	return n / (float)(UINT32_C(1) << 31);
}

#endif
