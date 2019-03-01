#ifndef mul_f1_f2_f3_h
#define mul_f1_f2_f3_h

#include "parameters.h"
#if F1F2F3 == 1

#include "internal_structs.h"





#ifdef __cplusplus
extern "C" {
#endif

	void mul_F1F2F3_par3_asm(PKEY3_CACHE_STRUCT key);	// F1* F2 * h || F3 * h
	void mul_F1F2F3_par3_plus_only_asm(PKEY3_CACHE_STRUCT key);
	void mul3_F1F2F3_par3_asm(PKEY3_CACHE_STRUCT key);
	void F1_h_plus_F2_asm(PNTRUPrimePolinomStruct3 key, signed short *h, signed short *result);
	void F3_h_asm(PNTRUPrimePolinomStruct3 key, signed short *h, signed short *result);


#ifdef __cplusplus
}
#endif
#endif

#endif
