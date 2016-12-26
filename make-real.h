/*
 * Integer to real conversion functions.
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


/*
 * The library is meant to be used with a PRNG producing integers to turn them
 * into a random real numbers in the range [0.0, 1.0).  The output of the
 * functions is as uniform as the source arguments and is guaranteed to be
 * non-negative and less then one.
 *
 * See https://mina86.com/2016/random-reals/ for discussion of the method.
 */


#include <math.h>
#include <stdint.h>
#include <string.h>
#include <float.h>


#if defined(__STDC_IEC_559__)
#  define make_real__is_iec559(type) 1
#elif defined(__cplusplus)
#  include <limits>
#  define make_real__is_iec559(type) std::numeric_limits<type>::is_iec559
#else
#  define make_real__is_iec559(type) 0
#endif

#if FLT_RADIX != 2
#  error "The library requires FLT_RADIX to be 2"
#endif


/**
 * Constructs a real in the [0, 1) range from given unsigned integer.  Provided
 * the argument is uniformly distributed, the result will be uniformly
 * distributed as well.
 *
 * Only the 23 most significant bits of the argument are used (which is the
 * maximum possible for IEEE 759 single precision floating point numbers).
 *
 * @param x 32-bit unsigned integer of which 23 most significant bits will be
 *     converted into a single precision floating point number.
 * @return A float in the [0.0, 1.0) range (i.e. non-negative number less than
 *     one).
 */
static inline float make_float(uint32_t x) {
	if (make_real__is_iec559(float)) {
		float ret;
		x = (UINT32_C(127) << 23) | (x >> 9);
		memcpy(&ret, &x, sizeof ret);
		return ret - 1.0f;
	} else {
		const int shift = FLT_MANT_DIG < 24 ? -(FLT_MANT_DIG - 1) : -23;
		return ldexpf(x >> (32 + shift), shift);
	}
}

/**
 * Constructs a real in the [0, 1) range from given unsigned integer.  Provided
 * the argument is uniformly distributed, the result will be uniformly
 * distributed as well.
 *
 * Only the 52 most significant bits of the argument are used (which is the
 * maximum possible for IEEE 759 double precision floating point numbers).
 *
 * @param x 64-bit unsigned integer of which 52 most significant bits will be
 *     converted into a double precision floating point number.
 * @return A double in the [0.0, 1.0) range (i.e. non-negative number less than
 *     one).
 */
static inline double make_double(uint64_t x) {
	if (make_real__is_iec559(double)) {
		double ret;
		x = (UINT64_C(1023) << 52) | (x >> 12);
		memcpy(&ret, &x, sizeof ret);
		return ret - 1.0;
	} else {
		const int shift = DBL_MANT_DIG < 53 ? -(DBL_MANT_DIG - 1) : -52;
		return ldexp(x >> (64 + shift), shift);
	}
}
