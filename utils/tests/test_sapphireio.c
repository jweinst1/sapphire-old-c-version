#include "sapphire-io.h"
#include "test-tools.h"

static FILE* 
_create_temp_file(const char* data)
{
	FILE* fp;
	fp = tmpfile();
	fputs(data, fp);
	rewind(fp);
	return fp;
}


void test_io_callback(const char* data, void** args)
{
	int* iptr = args[0];
	sscanf(data, "%d", iptr);
}

static void test_sapphire_io_read_chunk(void)
{
	FILE* testfp;
	const char* writ = "100";
	int readint = 0;
	het_arr_t args = {&readint, NULL};
	sapphire_io_read_cb reader = &test_io_callback;
	testfp = _create_temp_file(writ);
	TEST_CHECK_POINT(sapphire_io_read_chunk(testfp, reader, args));
	TEST_CHECK_POINT(readint == 100);
}

static void test_sapphire_io_size_file(void)
{
	FILE* testfp;
	size_t fsz;
	const char* writ = "1000";
	testfp = _create_temp_file(writ);
	sapphire_io_size_file(testfp, &fsz);
	TEST_CHECK_POINT(fsz == 4);
}

int main(int argc, char const *argv[])
{
	test_sapphire_io_read_chunk();
	test_sapphire_io_size_file();
	return 0;
}
