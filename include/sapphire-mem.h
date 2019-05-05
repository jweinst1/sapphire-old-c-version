#ifndef SAPPHIRE_UTILS_MEM_H
#define SAPPHIRE_UTILS_MEM_H

/**
 * @file Handles memory management and allocation
 */

#include <stdlib.h>
#ifdef SAPPHIRE_MEMORY_DEBUG_MODE
#  include <stdio.h>
#endif

/**
 * If memory debug is turned on, calls to malloc, calloc, relloc, and free are secretly also reported
 * via stdout.
 */
#ifdef SAPPHIRE_MEMORY_DEBUG_MODE
#  define sapphire_malloc(mem_size) (malloc(mem_size) + (0 * printf("SAPPHIREMEM - (malloc) size:%lu, line:%u, file:%s\n", (unsigned long)mem_size, __LINE__, __FILE__)))
#  define sapphire_calloc(mem_size) (calloc(mem_size, 0) + (0 * printf("SAPPHIREMEM - (calloc) size:%lu, line:%u, file:%s\n", (unsigned long)mem_size, __LINE__, __FILE__)))
#  define sapphire_realloc(mem_ptr, mem_size) \
              (realloc(mem_ptr, mem_size) + (0 * printf("SAPPHIREMEM - (realloc) size:%lu, addr:%p, line:%u, file:%s\n", mem_size, mem_ptr, __LINE__, __FILE__)))
#  define sapphire_free(mem_ptr) free(mem_ptr); printf("SAPPHIREMEM - (free) addr:%p, line:%u, file:%s\n", mem_ptr, __LINE__, __FILE__);
#else
#  define sapphire_malloc(mem_size) (malloc(mem_size))
#  define sapphire_realloc(mem_ptr, mem_size) (realloc(mem_ptr, mem_size))
#  define sapphire_calloc(mem_size) (calloc(mem_size, 0)) 
#  define sapphire_free(mem_ptr) free(mem_ptr)
#endif

/*Exit code used for NULL on alloc*/
#define SAPPHIRE_MEMORY_OMM_EXIT 3
/**
 * Creates a clean string with room for a '\0'
 * Must be freed when done.
 */
#define sapphire_mem_ch_str(size) ((char)sapphire_calloc(size + 1))
/**
 * Same as above but is not cleaned memory.
 */
#define sapphire_mem_raw_str(size) ((char)sapphire_malloc(size + 1))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __sapphire_mem_pool
{
	void* begin;
	void* cur;
	void* end;
} sapphire_mem_pool_t;

#ifdef __cplusplus
}
#endif

#define SAPPHIRE_MEM_POOL_SPACE(pool) (pool.end - pool.cur)
#define SAPPHIRE_MEM_POOL_LEN(pool) (pool.cur - pool.begin)
#define SAPPHIRE_MEM_POOL_CAP(pool) (pool.end - pool.begin)
#define SAPPHIRE_MEM_POOL_FULL(pool) (pool.end == pool.cur)
/**
 * Macro initializer for embedded mem pool
 * Does not clean, must be explicitly cleaned.
 */
#define SAPPHIRE_MEM_POOL_INIT(pool, init_size) \
                           pool.begin = sapphire_malloc(init_size); \
                           pool.cur = pool.begin; \
                           pool.end = pool.begin + init_size
/**
 * Grows the memory pool exponentially if not enough space is left.
 */
#define SAPPHIRE_MEM_POOL_GROW(pool) do { \
	size_t old_size = pool.end - pool.begin; \
	size_t old_len = pool.cur - pool.begin; \
	pool.begin = sapphire_realloc(pool.begin, old_size * old_size); \
	if(pool.begin == NULL) exit(SAPPHIRE_MEMORY_OMM_EXIT); \
	pool.cur = pool.begin + old_len; \
	pool.end = pool.begin + (old_size * old_size); \
} while (0)
/**
 * This sets some variable to a void pointer within the memory pool.
 * This alloc routine can grow continuously if needed, in the chance
 * that the request size is more than the square of the current size.
 */
#define SAPPHIRE_MEM_POOL_ALLOC(pool, var, req_size) do { \
    while(req_size >= SAPPHIRE_MEM_POOL_SPACE(pool)) SAPPHIRE_MEM_POOL_GROW(pool); \
    var = pool.cur; \
    pool.cur += req_size; \
} while (0)
/**
 * Similar to alloc but accounts for size based on type
 */
#define SAPPHIRE_MEM_POOL_NEW(pool, var, type, count) SAPPHIRE_MEM_POOL_ALLOC(pool, var, (sizeof(type) * count))
/**
 * destroys and frees all the memory within the memory pool
 */
#define SAPPHIRE_MEM_POOL_DESTROY(pool) free(pool.begin)


#endif // SAPPHIRE_UTILS_MEM_H
