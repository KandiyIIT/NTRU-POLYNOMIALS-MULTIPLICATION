#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "parameters.h"

#if F1F2F3 == 1
int print_result_F1F2F3(FILE *f);
int test_gen_all_keys_F1F2F3();
#else
int print_result(FILE *f);
int test_gen_all_keys();
#endif

int paral = 1;
int main()
{
	int res;
	set_const_16();
	FILE *file = 0;
	char fname[256];
	int i;
#if F1F2F3 == 1
	sprintf_s(fname, 256, "Test_F1F2F3_%d.txt", K);
	fopen_s(&file, fname, "wt");
	res = test_gen_all_keys_F1F2F3();
	for (i = 0; i < 100; i++)
	{
		res = print_result_F1F2F3(file);

	}
	fclose(file);
#else

	sprintf_s(fname, 256, "Test_%d.txt", K);
	fopen_s(&file, fname, "wt");
	res = test_gen_all_keys();
	for (i = 0; i < 100; i++)
	{
		res = print_result(file);

	}
	fclose(file);
#endif

	return 0;

}
