#include "parameters.h"
#if F1F2F3 == 1
#include <omp.h>

#include <float.h>

#include "mul_f1_f2_f3.h"
#include "internal_structs.h"


#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <immintrin.h>


static __inline__ unsigned long long __rdtsc(void)
{
	unsigned hi, lo;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

#endif


void mul_F1F2F3_par3_asm(PKEY3_CACHE_STRUCT key)
{

__m256i r0, r1, r2, r3, r4, r5, r6, r7, r13 = q256_16, r14 = q256_2_16;
typedef void (*ASM_FUN)(PNTRUPrimePolinomStruct3 key, signed short *h, signed short *result);
ASM_FUN fun[2] = { F1_h_plus_F2_asm, F3_h_asm };
signed short *res[2] = { key->result1, key->internal_result };
int i;
#pragma omp parallel for
for (i = 0; i < 2; i++)
{
	fun[i](&key->r3, key->h, res[i]);
}


	int k = 0;

	__m256i*res0 = (__m256i*) res[0];
	__m256i*res1 = (__m256i*) res[1];

	for (i = 0; i < N16_ / 8; i++)
	{
		r0 = _mm256_add_epi16(res0[k], res1[k]);
		r1 = _mm256_add_epi16(res0[k + 1], res1[k + 1]);
		r2 = _mm256_add_epi16(res0[k + 2], res1[k + 2]);
		r3 = _mm256_add_epi16(res0[k + 3], res1[k + 3]);
		r4 = _mm256_add_epi16(res0[k + 4], res1[k + 4]);
		r5 = _mm256_add_epi16(res0[k + 5], res1[k + 5]);
		r6 = _mm256_add_epi16(res0[k + 6], res1[k + 6]);
		r7 = _mm256_add_epi16(res0[k + 7], res1[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13))));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13))));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13))));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13))));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13))));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13))));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13))));

		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));
		_mm256_store_si256(res0 + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r14))));
		_mm256_store_si256(res0 + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r14))));
		_mm256_store_si256(res0 + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r14))));
		_mm256_store_si256(res0 + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r14))));
		_mm256_store_si256(res0 + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r14))));
		_mm256_store_si256(res0 + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r14))));
		_mm256_store_si256(res0 + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r14))));
		k += 8;
	}
	for (; k < N16_; k++)
	{
		r0 = _mm256_add_epi16(res0[k], res1[k]);
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));

	}


}

void mul_F1F2F3_par3_plus_only_asm(PKEY3_CACHE_STRUCT key)
{

	__m256i r0, r1, r2, r3, r4, r5, r6, r7, r13 = q256_16;
	typedef void(*ASM_FUN)(PNTRUPrimePolinomStruct3 key, signed short *h, signed short *result);
	ASM_FUN fun[2] = { F1_h_plus_F2_asm, F3_h_asm };
	signed short *res[2] = { key->result1, key->internal_result };
	int i;
#pragma omp parallel for
	for (i = 0; i < 2; i++)
	{
		fun[i](&key->r3, key->h, res[i]);
	}

	

	int k = 0;

	__m256i*res0 = (__m256i*) res[0];
	__m256i*res1 = (__m256i*) res[1];

	for (i = 0; i < N16_ / 8; i++)
	{
		r0 = _mm256_add_epi16(res0[k], res1[k]);
		r1 = _mm256_add_epi16(res0[k + 1], res1[k + 1]);
		r2 = _mm256_add_epi16(res0[k + 2], res1[k + 2]);
		r3 = _mm256_add_epi16(res0[k + 3], res1[k + 3]);
		r4 = _mm256_add_epi16(res0[k + 4], res1[k + 4]);
		r5 = _mm256_add_epi16(res0[k + 5], res1[k + 5]);
		r6 = _mm256_add_epi16(res0[k + 6], res1[k + 6]);
		r7 = _mm256_add_epi16(res0[k + 7], res1[k + 7]);

		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
		_mm256_store_si256(res0 + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13)))));
		_mm256_store_si256(res0 + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13)))));
		_mm256_store_si256(res0 + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13)))));
		_mm256_store_si256(res0 + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13)))));
		_mm256_store_si256(res0 + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13)))));
		_mm256_store_si256(res0 + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13)))));
		_mm256_store_si256(res0 + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13)))));

		k += 8;
	}
	for (; k < N16_; k++)
	{
		r0 = _mm256_add_epi16(res0[k], res1[k]);
		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
	

	}


}

void mul3_F1F2F3_par3_asm(PKEY3_CACHE_STRUCT key)
{
	__m256i r0, r1, r2, r3, r4, r5, r6, r7, r13 = q256_16, r14 = q256_2_16;
	__m256i *op1[2] = { (__m256i *) key->result1, (__m256i *) key->result1 };
	__m256i *op2[2] = { (__m256i *) key->result1, (__m256i *) key->h };
	__m256i *res[2] = { (__m256i *) key->internal_result, (__m256i *) (key->internal_result + N16) };
	int i;

	mul_F1F2F3_par3_plus_only_asm (key);
	#pragma omp parallel for
	for (i = 0; i < 2; i++)
	{
		__m256i r0, r1, r2, r3, r4, r5, r6, r7;
		__m256i * src1 = op1[i], *src2 = op2[i];
		__m256i * dest = res[i];
		int j, k = 0;
		for (j = 0; j < N16_ / 8; j++)
		{
			r0 = _mm256_add_epi16(src1[k], src2[k]);
			r1 = _mm256_add_epi16(src1[k + 1], src2[k + 1]);
			r2 = _mm256_add_epi16(src1[k + 2], src2[k + 2]);
			r3 = _mm256_add_epi16(src1[k + 3], src2[k + 3]);
			r4 = _mm256_add_epi16(src1[k + 4], src2[k + 4]);
			r5 = _mm256_add_epi16(src1[k + 5], src2[k + 5]);
			r6 = _mm256_add_epi16(src1[k + 6], src2[k + 6]);
			r7 = _mm256_add_epi16(src1[k + 7], src2[k + 7]);

			_mm256_store_si256(dest + k,  _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
			_mm256_store_si256(dest + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13)))));
			_mm256_store_si256(dest + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13)))));
			_mm256_store_si256(dest + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13)))));
			_mm256_store_si256(dest + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13)))));
			_mm256_store_si256(dest + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13)))));
			_mm256_store_si256(dest + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13)))));
			_mm256_store_si256(dest + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13)))));


			k += 8;
		}
		for (; k < N16_; k++)
		{
			r0 = _mm256_add_epi16(src1[k], src2[k]);
			_mm256_store_si256(dest + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));


		}


	}

	int k = 0;
	 __m256i * src1 = res[0], *src2 = res[1];
	 __m256i * dest = (__m256i *)key->result1;
	for (i = 0; i < N16_ / 8; i++)
	{
		r0 = _mm256_add_epi16(src1[k], src2[k]);
		r1 = _mm256_add_epi16(src1[k + 1], src2[k + 1]);
		r2 = _mm256_add_epi16(src1[k + 2], src2[k + 2]);
		r3 = _mm256_add_epi16(src1[k + 3], src2[k + 3]);
		r4 = _mm256_add_epi16(src1[k + 4], src2[k + 4]);
		r5 = _mm256_add_epi16(src1[k + 5], src2[k + 5]);
		r6 = _mm256_add_epi16(src1[k + 6], src2[k + 6]);
		r7 = _mm256_add_epi16(src1[k + 7], src2[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13))));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13))));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13))));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13))));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13))));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13))));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13))));

		_mm256_store_si256(dest + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));
		_mm256_store_si256(dest + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r14))));
		_mm256_store_si256(dest + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r14))));
		_mm256_store_si256(dest + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r14))));
		_mm256_store_si256(dest + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r14))));
		_mm256_store_si256(dest + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r14))));
		_mm256_store_si256(dest + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r14))));
		_mm256_store_si256(dest + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r14))));
		k += 8;
	}
	for (; k < N16_; k++)
	{
		r0 = _mm256_add_epi16(src1[k], src2[k]);
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		_mm256_store_si256(dest + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));

	}

}

#endif
