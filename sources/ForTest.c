#include "internal_structs.h"
#include "mul_f1_f2_f3.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <immintrin.h>
#endif

#define NKEYS	10000
#define GOOD	1
#define RAND	2
#define BAD		3
#define EQUAL	4



void R3ToStruct16(signed char* src, PIITR3_16  dest, int onesCount)
{
	unsigned short zero[N32], zero_count = 0;;
	unsigned short *p_values[3] = { dest->ones + onesCount, zero, dest->ones }, *pcur;
	unsigned short *p_counts[3] = { &dest->minusonesCount, &zero_count, &(dest->onesCount) };
	dest->minusonesCount = dest->onesCount = 0;
	signed char ind;
	int i;
	for (i = 0; i < N_; i++)
	{
		ind = src[i] + 1;
		pcur = p_values[ind];
		pcur[*p_counts[ind]] = i;
		*p_counts[ind] += 1;
	}
}

void StructToR3_16(signed char* dest, PIITR3_16  src)
{
	signed short *ind = src->ones;
	unsigned short count = src->onesCount, i;
	memset(dest, 0, N16);
	for (i = 0; i < count; i++)
		dest[ind[i]] = 1;
	ind = src->ones + src->onesCount;
	count = src->minusonesCount;
	for (i = 0; i < count; i++)
		dest[ind[i]] = -1;



}

extern int paral;

#if defined(__x86_64__)
 static __inline__ unsigned long long __rdtsc(void){
    unsigned hi,lo;
    __asm__ __volatile__("rdtsc":"=a"(lo),"=d"(hi));
    return  ((unsigned long long)lo)|((unsigned long long)hi);
}
#endif


#ifdef _MSC_VER
__declspec (align (32))
KEYS_STRUCI16  keys[NKEYS] = { 0 };
#else
KEYS_STRUCI16 keys[NKEYS] __attribute__((aligned(32))) = {0};
#endif

int cmp(const void *a, const void *b)
{
	signed long long *ua = (signed long long*)a, *ub = (signed long long*)b;
	return (int)(*ua - *ub);
}

double disper(long long *x, int n, double m)
{
	double s = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		double r = (x[i] - m) + 0.;
		s += r * r;
	}
	return s / n;

}
void test_gen_keys_(KEYS_STRUCI16 keys[], int type)
{
	int i, j, k;

	FILE *file;
	char fName[256];
	sprintf_s(fName, sizeof(fName), "%sKeys_%d.bin", type == GOOD ? "Good" : type == BAD ? "Bad" : type == RAND ? "Rand" : "Equal", K);
	fopen_s(&file, fName, "rb");
	if (file == 0)
	{


		for (i = 0; i < NKEYS; i++)
		{
			if (i != 0 && type == EQUAL)
			{
				keys[i] = keys[0];
				continue;
			}

			signed char key[N_] = { 0 };
			for (j = 0; j < N_; j++)
				keys[i].h[j] = rand() % Q_;
			memset(keys[i].h + N_, 0, (N16 - N_) * 2);
			int count = 0, ind, count_plus = 0;
			if (type == GOOD)
			{

				for (j = 0, k = N_ / 16 * 16; j < k;)
				{
					key[j] = 1;
					key[k] = -1;
					count += 2;
					count_plus++;
					j += 16; k -= 16;
					if (j >= k)
						break;
					key[j] = -1;
					key[k] = +1;
					count_plus++;
					count += 2;
					j += 16; k -= 16;
				}

				while (count < 2 * T_)
				{
					ind = rand() % N_;
					if (key[ind] == 0)
					{
						key[ind] = 1;
						count++;
						count_plus++;
					}
					if (count == 2 * T_)
						break;
					ind = rand() % N_;
					if (key[ind] == 0)
					{
						key[ind] = -1;
						count++;
					}
				}

			}
			if (type == BAD)
			{

				while (count < T_)
				{
					int ind = rand() % N_;
					while (ind % 16 == 0)
						ind = rand() % N_;

					if (key[ind] == 0)
					{
						key[ind] = 1;
						count_plus++;
						count++;
					}

				}

				while (count < 2 * T_)
				{
					int ind = rand() % N_;
					while (ind % 16 == 0)
						ind = rand() % N_;

					if (key[ind] == 0)
					{
						key[ind] = -1;
						count++;
					}

				}

			}
			if ((type == RAND) || (type == EQUAL))
			{
				{

					while (count < T_)
					{
						int ind = rand() % N_;

						if (key[ind] == 0)
						{
							key[ind] = 1;
							count_plus++;
							count++;
						}
					}
					while (count < 2 * T_)
					{

						ind = rand() % N_;
						if (key[ind] == 0)
						{
							key[ind] = -1;
							count++;
						}
					}
				}


			}

			R3ToStruct16(key, &keys[i].r3, count_plus);
		}
		fopen_s(&file, fName, "wb");
		fwrite(keys, NKEYS, sizeof(keys[0]), file);
	}
	else
	{
		fread(keys, NKEYS, sizeof(keys[0]), file);
	}
	fclose(file);
}

#if F1F2F3 == 1
int test_gen_keys_F1F2F3 (PKEY3_CACHE_STRUCT key, int type)
{
	int res = 0;
	int i, j, k, l;
	signed char f[N_];
	FILE *file;
	char fName[256];
	sprintf_s(fName, sizeof (fName), "F1F2F3%sKeys_%d.bin", type == GOOD ? "Good" : type == BAD ? "Bad" : type == RAND? "Rand" : "Equal", K);
	fopen_s(&file, fName, "rb");
	if (file == 0)
	{
		int type1;
		if (type == EQUAL)
		{
			type = RAND;
			type1 = EQUAL;
		}
		memset(key, 0, NKEYS * sizeof(KEY3_CACHE_STRUCT));

		for (i = 0; i < NKEYS; i++)
		{

			
			if (i != 0 && type1 == EQUAL)
			{
				key[i] = key[0];
				continue;
			}
			signed short *ones1 = key[i].r3.ones1;
			signed short *minusones1 = key[i].r3.minusones1;
			signed short *ones2 = key[i].r3.ones2;
			signed short *minusones2 = key[i].r3.minusones2;
			signed short *ones3 = key[i].r3.ones3;
			signed short *minusones3 = key[i].r3.minusones3;
			signed short t;
			for (j = 0; j < N_; j++)
				key[i].h[j] = rand() % Q_;


			{
				memset(f, 0, N_);
				for (j = 0; j < D1_;)
				{
					t = (rand() % (N_));
					if (type == GOOD)
						t = t & ~15;
					if (type == BAD)
					{
						while ((t & 15) == 0)
							t = (rand() % (N_));
					}

					if (f[t] == 0)
					{
						f[t] = 1;
						j++;

					}
				}

				for (j = 0; j < D1_;)
				{
					t = (rand() % (N_));

					if (type == GOOD)
						t = t & ~15;
					if (type == BAD)
					{
						while ((t & 15) == 0)
							t = (rand() % (N_));
					}

					if (f[t] == 0)
					{
						f[t] = -1;
						j++;

					}
				}

				j = 0; k = 0;
				for (l = 0; l < N_; l++)
				{
					if (f[l] == 1)
						ones1[j++] = l;
					if (f[l] == -1)
						minusones1[k++] = l;
				}

				memset(f, 0, N_);
				for (l = 0; l < D2_;)
				{
					t = (rand() % (N_));
					if (type == GOOD)
						t = t & ~15;
					if (type == BAD)
					{
						while ((t & 15) == 0)
							t = (rand() % (N_));
					}

					if (f[t] == 0)
					{
						f[t] = 1;
						l++;

					}
				}

				for (l = 0; l < D2_;)
				{
					t = (rand() % (N_));
					if (type == GOOD)
						t = t & ~15;
					if (type == BAD)
					{
						while ((t & 15) == 0)
							t = (rand() % (N_));
					}

					if (f[t] == 0)
					{
						f[t] = -1;
						l++;

					}
				}

				j = 0; k = 0;
				for (l = 0; l < N_; l++)
				{
					if (f[l] == 1)
						ones2[j++] = l;
					if (f[l] == -1)
						minusones2[k++] = l;
				}


				memset(f, 0, N_);
				for (l = 0; l < D3_;)
				{
					t = (rand() % (N_));
					if (type == GOOD)
						t = t & ~15;
					if (type == BAD)
					{
						while ((t & 15) == 0)
							t = (rand() % (N_));
					}

					if (f[t] == 0)
					{
						f[t] = 1;
						l++;

					}
				}

				for (l = 0; l < D3_;)
				{
					t = (rand() % (N_));

					if (f[t] == 0)
					{
						f[t] = -1;
						l++;

					}
				}

				j = 0; k = 0;
				for (l = 0; l < N_; l++)
				{
					if (f[l] == 1)
						ones3[j++] = l;
					if (f[l] == -1)
						minusones3[k++] = l;
				}
			}


		}
		fopen_s(&file, fName, "wb");
		if (file == 0)
			return 1;

		fwrite(key, NKEYS, sizeof(KEY3_CACHE_STRUCT), file);

	}
	else
	{
		fread(key, NKEYS, sizeof(KEY3_CACHE_STRUCT), file);
	}
	fclose(file);
	return 0;


}

int test_gen_all_keys_F1F2F3()
{
#ifdef _MSC_VER
	__declspec (align (32))
	static KEY3_CACHE_STRUCT key[NKEYS];
#else
    static KEY3_CACHE_STRUCT key[NKEYS] __attribute__((aligned(32)));
#endif
	int res;
	res = test_gen_keys_F1F2F3(key, EQUAL);
	if (res == 0)
		res = test_gen_keys_F1F2F3(key, GOOD);
	if (res == 0)
		res = test_gen_keys_F1F2F3(key, BAD);
	if (res == 0)
		res = test_gen_keys_F1F2F3(key, RAND);
	return res;
}
#endif


#ifdef _MSC_VER
__declspec (align (32))
	KEYS_STRUCI16 keys[NKEYS];
#else
    KEYS_STRUCI16 keys[NKEYS] __attribute__((aligned(32)));
#endif

void write_mul_result(KEYS_STRUCI16 keys[NKEYS],const char* filename){
    FILE* f;
	f=fopen(filename, "wb");
    if(f==NULL){
        printf("error!\n");
        return;
    }
	for (int i = 0; i < NKEYS; i++)
	{
		fwrite(keys[i].res, sizeof(keys[i].res), 1, f);
	}
	fclose(f);
}

#if F1F2F3 == 1
void write_mul_result_f1f2f3(KEY3_CACHE_STRUCT keys[NKEYS],const char* filename){
    FILE* f;
	f= fopen(filename, "wb");
    if(f==NULL){
        printf("error!\n");
        return;
    }
	for (int i = 0; i < NKEYS; i++)
	{
		fwrite(keys[i].result1, sizeof(keys[i].result1), 1, f);
	}
	fclose(f);
}
#endif

int test_gen_all_keys()
{
	
	int res = 0;
	test_gen_keys_(keys, EQUAL);
	//if (res == 0)
		test_gen_keys_(keys, GOOD);
	//if (res == 0)
		test_gen_keys_(keys, BAD);
	//if (res == 0)
		test_gen_keys_(keys, RAND);
	return res;
}

void gen_test_keys()
{
	FILE *f;
	char fn[256];
	int i;
	sprintf_s(fn, sizeof(fn), "good_keys%d.bin", K);
	fopen_s(&f, fn, "wb");
	test_gen_keys_(keys, GOOD);
	for (i = 0; i < NKEYS; i++)
	{
		fwrite(keys[i].h, sizeof(keys[i].h), 1, f);
		fwrite(&keys[i].r3, sizeof(keys[i].r3), 1, f);
		fwrite(&keys[i].res_internal, 512, 1, f);

	}
	fclose(f);

	sprintf_s(fn, sizeof(fn), "bad_keys%d.bin", K);
	fopen_s(&f, fn, "wb");

	test_gen_keys_(keys, BAD);
	for (i = 0; i < NKEYS; i++)
	{
		fwrite(keys[i].h, sizeof(keys[i].h), 1, f);
		fwrite(&keys[i].r3, sizeof(keys[i].r3), 1, f);
		fwrite(&keys[i].res_internal, 512, 1, f);

	}
	fclose(f);

	sprintf_s(fn, sizeof(fn), "rand_keys%d.bin", K);
	fopen_s(&f, fn, "wb");

	test_gen_keys_(keys, RAND);
	for (i = 0; i < NKEYS; i++)
	{
		fwrite(keys[i].h, sizeof(keys[i].h), 1, f);
		fwrite(&keys[i].r3, sizeof(keys[i].r3), 1, f);
		fwrite(&keys[i].res_internal, 512, 1, f);

	}
	fclose(f);
}

int read_test_keys_(KEYS_STRUCI16  keys[NKEYS], int type)
{
	int res = 0;
	FILE *f;
	char fn[256];
	if (type == EQUAL)
		sprintf_s(fn, sizeof(fn), "EqualKeys_%d.bin", K);
	else
	{
		if (type == GOOD)
			sprintf_s(fn, sizeof(fn), "GoodKeys_%d.bin", K);
		else if (type == BAD)
			sprintf_s(fn, sizeof(fn), "BadKeys_%d.bin", K);
		else sprintf_s(fn, sizeof(fn), "RandKeys_%d.bin", K);
	}
	fopen_s(&f, fn, "rb");

	res = f == 0;
	if (res == 0)
	{
		fread(keys, NKEYS, sizeof(KEYS_STRUCI16), f);
		fclose(f);
	}
	return res;


}

int read_good_test_keys()
{
	int res = read_test_keys_(keys, GOOD);
	return res;
}

int read_bad_test_keys()
{
	int res = read_test_keys_(keys, BAD);
	return res;
}
int read_rand_test_keys()
{
	int res = read_test_keys_(keys, RAND);
	return res;
}

int read_equal_test_keys()
{
	int res = read_test_keys_(keys, EQUAL);
	return res;
}
long long GoodTacts[NKEYS], SortGoodTacts[NKEYS], BadTacts[NKEYS], SortBadTacts[NKEYS], RandTacts[NKEYS], SortRandTacts[NKEYS],

EqualRandTacts[NKEYS], SortEqualRandTacts[NKEYS];
void testmul(long long tacts[], long long sorttacts[], char *fn)
{
	int i, j;
	FILE *f;
	unsigned long long min, start, dif;

	if (paral == 1)
	{
		for (i = 0; i < NKEYS; i++)
		{
			if (i != 0 && i % 1000 == 0)
				printf("i = %d\n", i);
			min = 0xFFFFFFFFFFFFFFFFL;
			for (j = 0; j < 100; j++)

			{
				start = __rdtsc();

				mul_opt16_par3_asm(&keys[i]);

				dif = __rdtsc() - start;
				if (dif < min) min = dif;
			}
			tacts[i] = min;

		}
	}

	memcpy(sorttacts, tacts, NKEYS * sizeof(sorttacts[0]));
	qsort(sorttacts, NKEYS, sizeof(long long), cmp);

	fopen_s(&f, fn, "wb");
	fwrite(sorttacts, NKEYS, sizeof(long long), f);
	fclose(f);

}

void testmul_bershtein(long long tacts[], long long sorttacts[], char *fn)
{
    signed char tmp_ber[N16] __attribute__((aligned(32)));
    signed short res_ber[N16] __attribute__((aligned(32)));
    
	int i, j;
	FILE *f;
	unsigned long long min, start, dif;

		for (i = 0; i < NKEYS; i++)
		{
			if (i != 0 && i % 1000 == 0)
				printf("i = %d\n", i);
			min = 0xFFFFFFFFFFFFFFFFL;
			for (j = 0; j < 100; j++)

			{
                StructToR3_16(tmp_ber,&keys[i].r3);
				start = __rdtsc();
                rq_mult(res_ber,&keys[i].h,tmp_ber);
				dif = __rdtsc() - start;

				if (dif < min) min = dif;
			}
			tacts[i] = min;

		}



	memcpy(sorttacts, tacts, NKEYS * sizeof(sorttacts[0]));
	qsort(sorttacts, NKEYS, sizeof(long long), cmp);

	fopen_s(&f, fn, "wb");
	fwrite(sorttacts, NKEYS, sizeof(long long), f);
	fclose(f);

}

#if F1F2F3  == 1
void testmulF1F2F3(long long tacts[], long long sorttacts[], PKEY3_CACHE_STRUCT Keys, char *fn )
{
	int i, j;
	FILE *f;
	unsigned long long min, start, dif;

#ifdef _MSC_VER
	__declspec (align (32))
		KEY3_CACHE_STRUCT Key;
#else
    KEY3_CACHE_STRUCT Key __attribute__((aligned(32)));
#endif
	{
		for (i = 0; i < NKEYS; i++)
		{
			Key = Keys[i];
			if (i != 0 && i % 1000 == 0)
				printf("i = %d\n", i);
			min = 0xFFFFFFFFFFFFFFFFL;
			for (j = 0; j < 100; j++)

			{
				start = __rdtsc();

				mul_F1F2F3_par3_asm (&Key);
				dif = __rdtsc() - start;
				if (dif < min) min = dif;
			}
			tacts[i] = min;

		}
	}
	
	memcpy(sorttacts, tacts, NKEYS * sizeof(sorttacts[0]));
	qsort(sorttacts, NKEYS, sizeof(long long), cmp);

	fopen_s(&f, fn, "wb");
	fwrite(sorttacts, NKEYS, sizeof(long long), f);
	fclose(f);

}



void testmulEqual(long long tacts[], long long sorttacts[], PKEY3_CACHE_STRUCT Keys, char *fn)
{
	int i, j;
	FILE *f;
	unsigned long long min, start, dif;
	if (paral == 1)
	{
		for (i = 0; i < NKEYS; i++)
		{
			if (i != 0 && i % 1000 == 0)
				printf("i = %d\n", i);
			min = 0xFFFFFFFFFFFFFFFFL;
			for (j = 0; j < 100; j++)
			{
				start = __rdtsc();
				mul_opt16_par3_asm(&keys[0]);
				dif = __rdtsc() - start;
				if (dif < min) min = dif;
			}
			tacts[i] = min;

		}
	}


	memcpy(sorttacts, tacts, NKEYS * sizeof(sorttacts[0]));
	qsort(sorttacts, NKEYS, sizeof(long long), cmp);

	fopen_s(&f, fn, "wb");
	fwrite(sorttacts, NKEYS, sizeof(long long), f);
	fclose(f);

}
#endif

#if F1F2F3 == 1
void testmulF1F2F3Equal(long long tacts[], long long sorttacts[], PKEY3_CACHE_STRUCT Keys, char *fn)
{
	int i, j;
	FILE *f;
	unsigned long long min, start, dif;

	{
		for (i = 0; i < NKEYS; i++)
		{
			KEY3_CACHE_STRUCT key = Keys[0];
			if (i != 0 && i % 1000 == 0)
				printf("i = %d\n", i);
			min = 0xFFFFFFFFFFFFFFFFL;
			for (j = 0; j < 100; j++)
			{
				start = __rdtsc();

				mul_F1F2F3_par3_asm(&key);
				dif = __rdtsc() - start;
				if (dif < min) min = dif;
			}
			tacts[i] = min;

		}
	}
	
	memcpy(sorttacts, tacts, NKEYS * sizeof(sorttacts[0]));
	qsort(sorttacts, NKEYS, sizeof(long long), cmp);

	fopen_s(&f, fn, "wb");
	fwrite(sorttacts, NKEYS, sizeof(long long), f);
	fclose(f);

}
#endif
#if F1F2F3 == 1

#ifdef _MSC_VER
__declspec (align (32))
	KEY3_CACHE_STRUCT keyF1F2F3[NKEYS];
#else
    KEY3_CACHE_STRUCT keyF1F2F3[NKEYS] __attribute__((aligned(32)));
#endif

int testF1F2F3()
{
	int res = 0;

	res = test_gen_keys_F1F2F3(keyF1F2F3, EQUAL);

	if (res == 0)
	{
		printf("Test equal keys\n");
		testmulF1F2F3(EqualRandTacts, SortEqualRandTacts, keyF1F2F3, "EqualTactsF1F2F3.bin");
        write_mul_result_f1f2f3(keyF1F2F3,"EqualTactsF1F2F3_result.bin");

	}


	res = test_gen_keys_F1F2F3(keyF1F2F3, GOOD);

	if (res == 0)
	{
		printf("Test good keys\n");
		testmulF1F2F3(GoodTacts, SortGoodTacts, keyF1F2F3, "GoodTactsF1F2F3.bin");
        write_mul_result_f1f2f3(keyF1F2F3,"GoodTactsF1F2F3_result.bin");
		
	}
	res = test_gen_keys_F1F2F3(keyF1F2F3, BAD);
	if (res == 0)
	{
		printf("Test bad keys\n");
		testmulF1F2F3 (BadTacts, SortBadTacts, keyF1F2F3, "BadTactsF1F2F3.bin");
        write_mul_result_f1f2f3(keyF1F2F3,"BadTactsF1F2F3_result.bin");
	}
	res = test_gen_keys_F1F2F3(keyF1F2F3, RAND);
	if (res == 0)
	{
		printf("Test rand keys\n");
		testmulF1F2F3 (RandTacts, SortRandTacts, keyF1F2F3, "RandTactsF1F2F3.bin");
        write_mul_result_f1f2f3(keyF1F2F3,"RandTactsF1F2F3_result.bin");

	}


	return res;
}

#endif
int test()
{
	int res;
	printf("sizeof (KEYS_STRUCI16) = %d\n", (int)(sizeof(KEYS_STRUCI16)));

	res = read_equal_test_keys();
	if (res == 0)
	{
		printf("Test equal keys\n");
		testmul(EqualRandTacts, SortEqualRandTacts, "EqualTacts.bin");
        write_mul_result(keys,"EqualTacts_result.bin");
	}

	res = read_good_test_keys();
	if (res == 0)
	{
		printf("Test good keys\n");
		testmul(GoodTacts, SortGoodTacts, "GoodTacts.bin");
        write_mul_result(keys,"GoodTacts_result.bin");
	}
	res = read_bad_test_keys();
	if (res == 0)
	{
		printf("Test bad keys\n");
		testmul(BadTacts, SortBadTacts, "BadTacts.bin");
        write_mul_result(keys,"BadTacts_result.bin");
	}
	res = read_rand_test_keys();
	if (res == 0)
	{
		printf("Test rand keys\n");
		testmul(RandTacts, SortRandTacts, "RandTacts.bin");
        write_mul_result(keys,"RandTacts_result.bin");
	
	}


	return res;
}

int test_bershtein()
{
	int res;
	printf("sizeof (KEYS_STRUCI16) = %d\n", (int)(sizeof(KEYS_STRUCI16)));

	res = read_equal_test_keys();
	if (res == 0)
	{
		printf("Test equal keys\n");
		testmul_bershtein(EqualRandTacts, SortEqualRandTacts, "EqualTacts.bin");
        write_mul_result(keys,"EqualTacts_result.bin");
	}

	res = read_good_test_keys();
	if (res == 0)
	{
		printf("Test good keys\n");
		testmul_bershtein(GoodTacts, SortGoodTacts, "GoodTacts.bin");
        write_mul_result(keys,"GoodTacts_result.bin");
	}
	res = read_bad_test_keys();
	if (res == 0)
	{
		printf("Test bad keys\n");
		testmul_bershtein(BadTacts, SortBadTacts, "BadTacts.bin");
        write_mul_result(keys,"BadTacts_result.bin");
	}
	res = read_rand_test_keys();
	if (res == 0)
	{
		printf("Test rand keys\n");
		testmul_bershtein(RandTacts, SortRandTacts, "RandTacts.bin");
        write_mul_result(keys,"RandTacts_result.bin");
	
	}


	return res;
}

double middle(long long *tacts, int count)
{
	int i;
	long long mid = 0;
	for (i = 0; i < count; i++)
	{
		mid += tacts[i];
	}
	return (mid + 0.) / count;
}

int print_result(FILE *f)
{
	static int test_number = 1, i;
	int res = test();
	int good_min_number = 0, bad_min_number = 0, rand_min_number = 0, equal_rand_min_number = 0;
	double disp;
	if (res == 0)
	{
		long long cur = SortGoodTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == GoodTacts[i])
			{
				good_min_number = i; break;
			}
		}
		cur = SortBadTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == BadTacts[i])
			{
				bad_min_number = i; break;
			}
		}

		cur = SortRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == RandTacts[i])
			{
				rand_min_number = i; break;
			}
		}

		cur = SortEqualRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == EqualRandTacts[i])
			{
				equal_rand_min_number = i; break;
			}
		}

		double m = middle(SortGoodTacts, NKEYS - 1000);
		disp = disper(SortGoodTacts, NKEYS - 1000, m);

		printf("GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);
		fprintf(f, "GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);

		m = middle(SortBadTacts, NKEYS - 1000);
		disp = disper(SortBadTacts, NKEYS - 1000, m);
		printf("BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);
		fprintf(f, "BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);

		m = middle(SortRandTacts, NKEYS - 1000);
		disp = disper(SortRandTacts, NKEYS - 1000, m);
		printf("RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);
		fprintf(f, "RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);

		m = middle(SortEqualRandTacts, NKEYS - 1000);
		disp = disper(SortEqualRandTacts, NKEYS - 1000, m);
		printf("Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		fprintf(f, "Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		test_number++;


	}
	return res;
}

int print_result_bershtein(FILE *f)
{
	static int test_number = 1, i;
	int res = test_bershtein();
	int good_min_number = 0, bad_min_number = 0, rand_min_number = 0, equal_rand_min_number = 0;
	double disp;
	if (res == 0)
	{
		long long cur = SortGoodTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == GoodTacts[i])
			{
				good_min_number = i; break;
			}
		}
		cur = SortBadTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == BadTacts[i])
			{
				bad_min_number = i; break;
			}
		}

		cur = SortRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == RandTacts[i])
			{
				rand_min_number = i; break;
			}
		}

		cur = SortEqualRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == EqualRandTacts[i])
			{
				equal_rand_min_number = i; break;
			}
		}

		double m = middle(SortGoodTacts, NKEYS - 1000);
		disp = disper(SortGoodTacts, NKEYS - 1000, m);

		printf("GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);
		fprintf(f, "GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);

		m = middle(SortBadTacts, NKEYS - 1000);
		disp = disper(SortBadTacts, NKEYS - 1000, m);
		printf("BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);
		fprintf(f, "BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);

		m = middle(SortRandTacts, NKEYS - 1000);
		disp = disper(SortRandTacts, NKEYS - 1000, m);
		printf("RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);
		fprintf(f, "RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);

		m = middle(SortEqualRandTacts, NKEYS - 1000);
		disp = disper(SortEqualRandTacts, NKEYS - 1000, m);
		printf("Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		fprintf(f, "Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		test_number++;


	}
	return res;
}

#if F1F2F3 == 1
int print_result_F1F2F3(FILE *f)
{
	static int test_number = 1, i;
	int res = testF1F2F3();
	int good_min_number = 0, bad_min_number = 0, rand_min_number = 0, equal_rand_min_number = 0;
	double disp;
	if (res == 0)
	{
		long long cur = SortGoodTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == GoodTacts[i])
			{
				good_min_number = i; break;
			}
		}
		cur = SortBadTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == BadTacts[i])
			{
				bad_min_number = i; break;
			}
		}

		cur = SortRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == RandTacts[i])
			{
				rand_min_number = i; break;
			}
		}

		cur = SortEqualRandTacts[0];
		for (i = 1; i < NKEYS - 1000; i++)
		{
			if (cur == EqualRandTacts[i])
			{
				equal_rand_min_number = i; break;
			}
		}

		double m = middle(SortGoodTacts, NKEYS - 1000);
		disp = disper(SortGoodTacts, NKEYS - 1000, m);

		printf("GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);
		fprintf(f, "GOOD	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortGoodTacts[0], good_min_number, m, disp);

		m = middle(SortBadTacts, NKEYS - 1000);
		disp = disper(SortBadTacts, NKEYS - 1000, m);
		printf("BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);
		fprintf(f, "BAD	%d: min = %I64d min_number = %d middle = %lg  disp = %lg\n", test_number, SortBadTacts[0], bad_min_number, m, disp);

		m = middle(SortRandTacts, NKEYS - 1000);
		disp = disper(SortRandTacts, NKEYS - 1000, m);
		printf("RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);
		fprintf(f, "RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortRandTacts[0], rand_min_number, m, disp);

		m = middle(SortEqualRandTacts, NKEYS - 1000);
		disp = disper(SortEqualRandTacts, NKEYS - 1000, m);
		printf("Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		fprintf(f, "Equal RAND	%d: min = %I64d min_number = %d middle = %lg disp = %lg\n", test_number, SortEqualRandTacts[0], equal_rand_min_number, m, disp);

		test_number++;


	}
	return res;
}
#endif




