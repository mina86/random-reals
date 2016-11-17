#include <stdint.h>
#include <string.h>

#ifdef USE_BITS

#ifndef __STDC_IEC_559__
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
