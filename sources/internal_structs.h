#ifndef _ntruprime_iit_internal_h
#define _ntruprime_iit_internal_h
#include <string.h>
#ifndef _TACTS
#include <omp.h>
#endif

#include "parameters.h"
#ifdef _TEST_VECTORS
#include "TestVector.h"
#endif

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <immintrin.h>
#endif
#ifdef _WRITEFILE
#include <stdio.h>
#endif

#define AVX_LEN	32




#ifndef _MSC_VER
#pragma pack(push,1)
#endif
typedef struct
{
	short onesCount, minusonesCount;
	short ones[2 * N_ / 3 + 1];
	
}IITR3_16, *PIITR3_16;





	typedef struct
	{
		signed short h[N16 + 16];
		signed short res_internal[16 * 16 + N16 * 2 + 16];
		signed short res[N16];
		IITR3_16 r3;
		signed char temp[32 - sizeof(IITR3_16) % 32];
	}KEYS_STRUCI16, *PKEYS_STRUCI16;

	#if F1F2F3 == 1
    
		typedef struct
		{
			unsigned short ones1[D1_], minusones1[D1_];
			unsigned short ones2[D2_], minusones2[D2_];
			unsigned short ones3[D3_], minusones3[D3_];

		}NTRUPrimePolinomStruct3, *PNTRUPrimePolinomStruct3;


		typedef struct
		{
			short  h[N16 + AVX_LEN / 2];	// 0, 768 * 2 = 1536  
			short  internal_result[16 + N16 * 2 + 32];	// 7680, 768 * 2 = 1536  
			short  result1[N16 + 16];	// 1536, 3072 
			NTRUPrimePolinomStruct3 r3;


			signed char temp[32 - (sizeof(NTRUPrimePolinomStruct3) % 32)];


		}KEY3_CACHE_STRUCT, *PKEY3_CACHE_STRUCT;


	#endif

	typedef struct
	{
		__m256i *res;
		unsigned short *plus, *minus;
		unsigned short plus_count, minus_count;
	}THREAD_PARAM_STRUCI16, *PTHREAD_PARAM_STRUCI16;

#ifndef _MSC_VER
#pragma pack(pop)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
	extern __m256i q256_16, q256_2_16, _0_16, _3_16, q256_2_MOD3, maska256_16;
	extern __m256i _FF_16, _F16, _2_16, _1_16, _1__16;


	void set_const_16();

#endif 
