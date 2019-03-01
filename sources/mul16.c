// temp.cpp: определяет точку входа для консольного приложения.
//
#ifndef __linux__
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "parameters.h"
#include "internal_structs.h"
#include <stdio.h>

__m256i q256_16, q256_2_16, _0_16, _3_16, q256_2_MOD3, maska256_16;
__m256i _FF_16, _F16, _2_16, _1_16,  _1__16;

void set_const_16()
{
	
	short maska[16] = { 0 };
	int i;
	for (i = 0; i < N_ % 16; i++)
		maska[i] = -1;
	_mm256_store_si256(&maska256_16, _mm256_lddqu_si256((__m256i*)maska));

	q256_16 = _mm256_set1_epi16(Q_);
	q256_2_16 = _mm256_set1_epi16(Q_ / 2);
	q256_2_MOD3 = _mm256_set1_epi16((Q_ / 2 + 2) / 3 * 3);
	_0_16 = _mm256_setzero_si256();
	_3_16 = _mm256_set1_epi16(3);
	_FF_16 = _mm256_set1_epi16(0xFF);
	_F16 = _mm256_set1_epi16(0xF); 
	_2_16 = _mm256_set1_epi16(2);
	_1_16 = _mm256_set1_epi16(1);
	_1__16 = _mm256_set1_epi16(-1);

}


void mul_opt16_par3_asm(PKEYS_STRUCI16 key)
{
	
	__m256i  res[3][N16_];
		
	unsigned short  num_plus = key->r3.onesCount, plus_por = (num_plus + 3) / 4;
	unsigned short  num_minus = key->r3.minusonesCount, minus_por = (num_minus) / 4;
	unsigned short  *pkplus = key->r3.ones, *pkminus = pkplus + num_plus;




	signed short *h = (signed short *)key->h;

	int thread, i;
	
	__m256i r13 = q256_16;
	
	THREAD_PARAM_STRUCI16 params[4];
	
	params[0].minus_count = minus_por; params[1].minus_count = minus_por;
	params[2].minus_count = minus_por; params[3].minus_count = num_minus - 3 * minus_por;

	params[0].plus_count = plus_por; params[1].plus_count = plus_por;
	params[2].plus_count = plus_por; params[3].plus_count = num_plus - 3 * plus_por;

	params[0].minus = pkminus; params[1].minus = pkminus + minus_por;
	params[2].minus = pkminus + minus_por + minus_por; params[3].minus = pkminus + 3 * minus_por;

	params[0].plus = pkplus; params[1].plus = pkplus + plus_por;
	params[2].plus = pkplus + plus_por + plus_por; params[3].plus = pkplus + 3 * plus_por;

	params[0].res = (__m256i*)key->res;
	params[1].res = res[0]; params[2].res = res[1]; params[3].res = res[2];
	

#pragma omp parallel for
	for (thread = 0; thread < 4; thread++){

		F_h_mul_asm (&params[thread], h);
    }
	


	
	__m256i *res0 = (__m256i *)key->res, *res1 = res[0], *res2 = res[1], *res3 = res[2];
	__m256i r0, r1, r2, r3, r4, r5, r6, r7, r14 = q256_2_16;


	int k = 0;
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

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));


		r0 = _mm256_add_epi16(r0, res2[k]);
		r1 = _mm256_add_epi16(r1, res2[k + 1]);
		r2 = _mm256_add_epi16(r2, res2[k + 2]);
		r3 = _mm256_add_epi16(r3, res2[k + 3]);
		r4 = _mm256_add_epi16(r4, res2[k + 4]);
		r5 = _mm256_add_epi16(r5, res2[k + 5]);
		r6 = _mm256_add_epi16(r6, res2[k + 6]);
		r7 = _mm256_add_epi16(r7, res2[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));


		r0 = _mm256_add_epi16(r0, res3[k]);
		r1 = _mm256_add_epi16(r1, res3[k + 1]);
		r2 = _mm256_add_epi16(r2, res3[k + 2]);
		r3 = _mm256_add_epi16(r3, res3[k + 3]);
		r4 = _mm256_add_epi16(r4, res3[k + 4]);
		r5 = _mm256_add_epi16(r5, res3[k + 5]);
		r6 = _mm256_add_epi16(r6, res3[k + 6]);
		r7 = _mm256_add_epi16(r7, res3[k + 7]);

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

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		
		r0 = _mm256_add_epi16(r0, res2[k]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r0 = _mm256_add_epi16(r0, res3[k]);
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));

	}



	_mm256_store_si256(res0 + k - 1, _mm256_and_si256(maska256_16, res0[k - 1]));

}



/*
void mul_opt16_par3_plus_asm(PKEYS_STRUCI16 key)
{

	__m256i  res[3][N16_];

	unsigned short  num_plus = key->r3.onesCount, plus_por = (num_plus + 3) / 4;
	unsigned short  num_minus = key->r3.minusonesCount, minus_por = (num_minus) / 4;
	unsigned short  *pkplus = key->r3.ones, *pkminus = pkplus + num_plus;




	signed short *h = (signed short *)key->h;

	int thread, i;

	__m256i r13 = q256_16;

	THREAD_PARAM_STRUCI16 params[4];

	params[0].minus_count = minus_por; params[1].minus_count = minus_por;
	params[2].minus_count = minus_por; params[3].minus_count = num_minus - 3 * minus_por;

	params[0].plus_count = plus_por; params[1].plus_count = plus_por;
	params[2].plus_count = plus_por; params[3].plus_count = num_plus - 3 * plus_por;

	params[0].minus = pkminus; params[1].minus = pkminus + minus_por;
	params[2].minus = pkminus + minus_por + minus_por; params[3].minus = pkminus + 3 * minus_por;

	params[0].plus = pkplus; params[1].plus = pkplus + plus_por;
	params[2].plus = pkplus + plus_por + plus_por; params[3].plus = pkplus + 3 * plus_por;

	params[0].res = (__m256i*)key->res;
	params[1].res = res[0]; params[2].res = res[1]; params[3].res = res[2];


#pragma omp parallel for
	for (thread = 0; thread < 4; thread++)
		F_h_mul_asm(&params[thread], h);




	__m256i *res0 = (__m256i *)key->res, *res1 = res[0], *res2 = res[1], *res3 = res[2];
	__m256i r0, r1, r2, r3, r4, r5, r6, r7;


	int k = 0;
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

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));


		r0 = _mm256_add_epi16(r0, res2[k]);
		r1 = _mm256_add_epi16(r1, res2[k + 1]);
		r2 = _mm256_add_epi16(r2, res2[k + 2]);
		r3 = _mm256_add_epi16(r3, res2[k + 3]);
		r4 = _mm256_add_epi16(r4, res2[k + 4]);
		r5 = _mm256_add_epi16(r5, res2[k + 5]);
		r6 = _mm256_add_epi16(r6, res2[k + 6]);
		r7 = _mm256_add_epi16(r7, res2[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));


		r0 = _mm256_add_epi16(r0, res3[k]);
		r1 = _mm256_add_epi16(r1, res3[k + 1]);
		r2 = _mm256_add_epi16(r2, res3[k + 2]);
		r3 = _mm256_add_epi16(r3, res3[k + 3]);
		r4 = _mm256_add_epi16(r4, res3[k + 4]);
		r5 = _mm256_add_epi16(r5, res3[k + 5]);
		r6 = _mm256_add_epi16(r6, res3[k + 6]);
		r7 = _mm256_add_epi16(r7, res3[k + 7]);

		_mm256_store_si256(res0 + k,  _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
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

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));

		r0 = _mm256_add_epi16(r0, res2[k]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r0 = _mm256_add_epi16(r0, res3[k]);
		_mm256_store_si256(res0 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));

	}



	_mm256_store_si256(res0 + k - 1, _mm256_and_si256(maska256_16, res0[k - 1]));

}
*/



/*
void mul3_opt16_par3_asm(PKEYS_STRUCI16 key)
{

	__m256i *res256 = (__m256i *)key->res, *h256 = (__m256i *)key->h;
	__m256i r0, r1, r2, r3, r4, r5, r6, r7, r14 = q256_2_16;
	__m256i r13 = q256_16;

	mul_opt16_par3_plus_asm(key);

	int k = 0, i;
	for (i = 0; i < N16_ / 8; i++)
	{
		r0 = _mm256_add_epi16(h256[k], res256[k]);
		r1 = _mm256_add_epi16(h256[k + 1], res256[k + 1]);
		r2 = _mm256_add_epi16(h256[k + 2], res256[k + 2]);
		r3 = _mm256_add_epi16(h256[k + 3], res256[k + 3]);
		r4 = _mm256_add_epi16(h256[k + 4], res256[k + 4]);
		r5 = _mm256_add_epi16(h256[k + 5], res256[k + 5]);
		r6 = _mm256_add_epi16(h256[k + 6], res256[k + 6]);
		r7 = _mm256_add_epi16(h256[k + 7], res256[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);
		r1 = _mm256_add_epi16(r1, res256[k + 1]);
		r2 = _mm256_add_epi16(r2, res256[k + 2]);
		r3 = _mm256_add_epi16(r3, res256[k + 3]);
		r4 = _mm256_add_epi16(r4, res256[k + 4]);
		r5 = _mm256_add_epi16(r5, res256[k + 5]);
		r6 = _mm256_add_epi16(r6, res256[k + 6]);
		r7 = _mm256_add_epi16(r7, res256[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);
		r1 = _mm256_add_epi16(r1, res256[k + 1]);
		r2 = _mm256_add_epi16(r2, res256[k + 2]);
		r3 = _mm256_add_epi16(r3, res256[k + 3]);
		r4 = _mm256_add_epi16(r4, res256[k + 4]);
		r5 = _mm256_add_epi16(r5, res256[k + 5]);
		r6 = _mm256_add_epi16(r6, res256[k + 6]);
		r7 = _mm256_add_epi16(r7, res256[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13))));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13))));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13))));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13))));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13))));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13))));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13))));

		_mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));
		_mm256_store_si256(res256 + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r14))));
		_mm256_store_si256(res256 + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r14))));
		_mm256_store_si256(res256 + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r14))));
		_mm256_store_si256(res256 + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r14))));
		_mm256_store_si256(res256 + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r14))));
		_mm256_store_si256(res256 + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r14))));
		_mm256_store_si256(res256 + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r14))));
		k += 8;
	}

	for (; k < N16_; k++)
	{
		r0 = _mm256_add_epi16(h256[k], res256[k]);
				
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		
		r0 = _mm256_add_epi16(r0, res256[k]);
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
				
		_mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r14))));

	}

}
*/


/*

void mul3_opt16_par3_plus_asm(PKEYS_STRUCI16 key)
{
	
	__m256i *res256 = (__m256i *)key->res, *h256 = (__m256i *)key->h;
	__m256i r0, r1, r2, r3, r4, r5, r6, r7;
	__m256i r13 = q256_16;

	mul_opt16_par3_plus_asm(key);

	int k = 0, i;
	for (i = 0; i < N16_ / 8; i++)
	{
		r0 = _mm256_add_epi16(h256[k], res256[k]);
		r1 = _mm256_add_epi16(h256[k + 1], res256[k + 1]);
		r2 = _mm256_add_epi16(h256[k + 2], res256[k + 2]);
		r3 = _mm256_add_epi16(h256[k + 3], res256[k + 3]);
		r4 = _mm256_add_epi16(h256[k + 4], res256[k + 4]);
		r5 = _mm256_add_epi16(h256[k + 5], res256[k + 5]);
		r6 = _mm256_add_epi16(h256[k + 6], res256[k + 6]);
		r7 = _mm256_add_epi16(h256[k + 7], res256[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);
		r1 = _mm256_add_epi16(r1, res256[k + 1]);
		r2 = _mm256_add_epi16(r2, res256[k + 2]);
		r3 = _mm256_add_epi16(r3, res256[k + 3]);
		r4 = _mm256_add_epi16(r4, res256[k + 4]);
		r5 = _mm256_add_epi16(r5, res256[k + 5]);
		r6 = _mm256_add_epi16(r6, res256[k + 6]);
		r7 = _mm256_add_epi16(r7, res256[k + 7]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));
		r1 = _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r1, r13)));
		r2 = _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r2, r13)));
		r3 = _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r3, r13)));
		r4 = _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r4, r13)));
		r5 = _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r5, r13)));
		r6 = _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r6, r13)));
		r7 = _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r7, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);
		r1 = _mm256_add_epi16(r1, res256[k + 1]);
		r2 = _mm256_add_epi16(r2, res256[k + 2]);
		r3 = _mm256_add_epi16(r3, res256[k + 3]);
		r4 = _mm256_add_epi16(r4, res256[k + 4]);
		r5 = _mm256_add_epi16(r5, res256[k + 5]);
		r6 = _mm256_add_epi16(r6, res256[k + 6]);
		r7 = _mm256_add_epi16(r7, res256[k + 7]);

		_mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
		_mm256_store_si256(res256 + k + 1, _mm256_sub_epi16(r1, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r1, r13), _mm256_cmpeq_epi16(r1, r13)))));
		_mm256_store_si256(res256 + k + 2, _mm256_sub_epi16(r2, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r2, r13), _mm256_cmpeq_epi16(r2, r13)))));
		_mm256_store_si256(res256 + k + 3, _mm256_sub_epi16(r3, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r3, r13), _mm256_cmpeq_epi16(r3, r13)))));
		_mm256_store_si256(res256 + k + 4, _mm256_sub_epi16(r4, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r4, r13), _mm256_cmpeq_epi16(r4, r13)))));
		_mm256_store_si256(res256 + k + 5, _mm256_sub_epi16(r5, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r5, r13), _mm256_cmpeq_epi16(r5, r13)))));
		_mm256_store_si256(res256 + k + 6, _mm256_sub_epi16(r6, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r6, r13), _mm256_cmpeq_epi16(r6, r13)))));
		_mm256_store_si256(res256 + k + 7, _mm256_sub_epi16(r7, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r7, r13), _mm256_cmpeq_epi16(r7, r13)))));

		k += 8;
	}

	for (; k < N16_; k++)
	{
		r0 = _mm256_add_epi16(h256[k], res256[k]);

		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);
		r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_cmpgt_epi16(r0, r13)));

		r0 = _mm256_add_epi16(r0, res256[k]);

		_mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));


	}

}
*/
