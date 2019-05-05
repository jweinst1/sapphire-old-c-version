#ifndef SAPPHIRE_UTILS_HET_ARRAY_H
#define SAPPHIRE_UTILS_HET_ARRAY_H

#include "compiler-status.h"
#include <stdlib.h>

typedef void* het_arr_t[];
typedef const void* het_const_t[];
typedef void** het_ptr_t;
typedef const void** het_const_ptr_t;

#define HET_ARR_IS_END(har) (*(har) == NULL)

/**
 * Convenience macro available on C99
 */
#ifdef SAPPHIRE_HAS_VARIADIC_ARGS
#  define HET_ARR_INIT(...) {__VA_ARGS__, NULL}
#  define HET_ARR_CREATE(name, ...) het_arr_t name = {__VA_ARGS__, NULL}
#endif

#define HET_ARR_LEN(har, len_i) do { \
	 len_i = 0; \
	 het_ptr_t ptr = har; \
	 while(*ptr++ != NULL) ++len_i; \
} while (0)

#endif // SAPPHIRE_UTILS_HET_ARRAY_H
