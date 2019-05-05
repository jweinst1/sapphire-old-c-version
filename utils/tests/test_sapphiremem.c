#include "sapphire-mem.h"
#include "test-tools.h"

static void test_sapphire_calloc(void)
{
	unsigned char* membyt = sapphire_calloc(10);
	TEST_CHECK_POINT(membyt[0] == 0);
	sapphire_free(membyt);
}

static void test_sapphire_mem_pool_init(void)
{
	sapphire_mem_pool_t pool;
	SAPPHIRE_MEM_POOL_INIT(pool, 1000);
	TEST_CHECK_POINT(pool.begin != NULL);
	TEST_CHECK_POINT((pool.end - pool.begin) == 1000);
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_SPACE(pool) == 1000);
	SAPPHIRE_MEM_POOL_DESTROY(pool);
}

static void test_sapphire_mem_pool_grow(void)
{
	sapphire_mem_pool_t pool;
	SAPPHIRE_MEM_POOL_INIT(pool, 100);
	SAPPHIRE_MEM_POOL_GROW(pool);
	TEST_CHECK_POINT(pool.begin != NULL);
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_SPACE(pool) == (100 * 100));
	SAPPHIRE_MEM_POOL_DESTROY(pool);
}

static void test_sapphire_mem_pool_alloc(void)
{
	sapphire_mem_pool_t pool;
	char* foo;
	char written;
	SAPPHIRE_MEM_POOL_INIT(pool, 100);
	SAPPHIRE_MEM_POOL_ALLOC(pool, foo, 10);
	foo[0] = 'g';
	TEST_CHECK_POINT(foo != NULL);
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_SPACE(pool) == 90);
	written = *(char*)(pool.begin);
	TEST_CHECK_POINT(written == 'g');
	SAPPHIRE_MEM_POOL_DESTROY(pool);
}

static void test_sapphire_mem_pool_new(void)
{
	sapphire_mem_pool_t pool;
	int* foo;
	int written;
	SAPPHIRE_MEM_POOL_INIT(pool, 100);
	SAPPHIRE_MEM_POOL_NEW(pool, foo, int, 50);
	foo[0] = 6;
	TEST_CHECK_POINT(foo != NULL);
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_CAP(pool) == (100 * 100));
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_LEN(pool) == (50 * sizeof(int)));
	written = *(int*)(pool.begin);
	TEST_CHECK_POINT(written == 6);
	SAPPHIRE_MEM_POOL_DESTROY(pool);
}

static void test_sapphire_mem_pool_new_2(void)
{
	sapphire_mem_pool_t pool;
	int* foo[3];
	SAPPHIRE_MEM_POOL_INIT(pool, 100);
	SAPPHIRE_MEM_POOL_NEW(pool, foo[0], int, 10);
	SAPPHIRE_MEM_POOL_NEW(pool, foo[1], int, 10);
	SAPPHIRE_MEM_POOL_NEW(pool, foo[2], int, 10);
	TEST_CHECK_POINT(foo[0] != NULL);
	TEST_CHECK_POINT(foo[1] != NULL);
	TEST_CHECK_POINT(foo[2] != NULL);
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_CAP(pool) == (100 * 100));
	TEST_CHECK_POINT(SAPPHIRE_MEM_POOL_LEN(pool) == (30 * sizeof(int)));

	TEST_CHECK_POINT(foo[0] != foo[1]);
	TEST_CHECK_POINT(foo[0] != foo[2]);
	TEST_CHECK_POINT(foo[1] != foo[2]);

	SAPPHIRE_MEM_POOL_DESTROY(pool);
}

int main(int argc, char const *argv[])
{
	test_sapphire_calloc();
	test_sapphire_mem_pool_init();
	test_sapphire_mem_pool_grow();
	test_sapphire_mem_pool_alloc();
	test_sapphire_mem_pool_new();
	test_sapphire_mem_pool_new_2();
	return 0;
}
