
%define AVX_LEN  		32
; Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
%define K    256
;K   384
;K   512

;F1F2F3   1
%define F1F2F3   0
; Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

 %if F1F2F3 == 1
	 %if K ==  256
		%define N   787
	%endif
	%if K ==  384
		%define N   1019
	%endif
	%if K == 512
		%define N   1301
	%endif
%else
	%if K ==  256
		%define N   761
	%endif
	%if K ==  384
		%define N   1031
	%endif
	%if K ==  512
		%define N   1301
	%endif
%endif

%if F1F2F3 == 1
	%define N787   787
	%define Q787   7307
	%define D1_787   12
	%define D2_787   12
	%define D3_787   15
	%define N1019   1019
	%define Q1019   8867
	%define D1_1019   13
	%define D2_1019   13
	%define D3_1019   31
	%define N1301   1301
	%define Q1301   11959
	%define D1_1301   15
	%define D2_1301   15
	%define D3_1301   48

	%define N1409   1409
	%define Q1409   13327
	%define D1_1409   16
	%define D2_1409   16
	%define D3_1409   43
	%if N == 787
		%define N_   N787
		%define Q_   Q787
		%define D1_   D1_787
		%define D2_   D2_787
		%define D3_   D3_787

	%endif
	%if N == 1019
		%define N_   N1019
		%define Q_   Q1019
		%define D1_   D1_1019
		%define D2_   D2_1019
		%define D3_   D3_1019
	%endif
	%if N == 1301
		%define N_   N1301
		%define Q_   Q1301
		%define D1_   D1_1301
		%define D2_   D2_1301
		%define D3_   D3_1301
	%endif
	%if N == 1409
		%define N_   N1409
		%define Q_   Q1409
		%define D1_   D1_1409
		%define D2_   D2_1409
		%define D3_   D3_1409
	%endif
%else
%if K == 256
	%define N761	 	761
	%define Q761	 	4591
		
	%define N881	 	881
	%define Q881	 	7673
	
	%define N883	 	883
	%define Q883	 	8089
 
	%define N907	 	907
	%define Q907	 	7727
 
	%define N953	 	953
	%define Q953	 	6343
 
	%define N967	 	967
	%define Q967	 	8243
 
	%define N971	 	971
	%define Q971	 	4871
	
	%define N977	 	977
	%define Q977	 	5783
 
	%define N991	 	991
	%define Q991	 	9349
 
	%define N997	 	997
	%define Q997	 	5393
		
	%define N1013	 	1013
	%define Q1013	 	7177
 

	%define N1019	 	1019
	%define Q1019	 	6691
 
	%define N1021	 	1021
	%define Q1021	 	5393

	%if N == 761
		%define N_   N761
		%define Q_   Q761
	%endif

	%if N == 881
		%define N_   N881
		%define Q_   Q881
	%endif

	%if N == 883
		%define N_   N883
		%define Q_   Q883
	%endif
	%if N == 907
		%define N_   N907
		%define Q_   Q907
	%endif
	%if N == 953
		%define N_   N953
		%define Q_   Q953
	%endif
	%if N == 967
		%define N_   N967
		%define Q_   Q967
	%endif
	%if N == 971
		%define N_   N971
		%define Q_   Q971
	%endif
	%if N == 977
		%define N_   N977
		%define Q_   Q977
	%endif
	%if N == 991
		%define N_   N991
		%define Q_   Q991
	%endif
	%if N == 997
		%define N_   N997
		%define Q_   Q997
	%endif
	
	%if N == 1013
		%define N_   N1013
		%define Q_   Q1013
	%endif

	%if N == 1019
		%define N_   N1019
		%define Q_   Q1019
	%endif
	%if N == 1021
		%define N_   N1021
		%define Q_   Q1021
	%endif
	
%endif

%if K == 384
	%define N1031    1031
	%define Q1031    8297
	%if N == 1031
		%define N_   N1031
		%define Q_   Q1031
	%endif
%endif 

%if K == 512


	%define N1301	 	1301
	%define Q1301	 	10427

	%define N1303	 	1303
	%define Q1303	 	10429

	%define N1307	 	1307
	%define Q1307	 	10499

	%define N1319	 	1319
	%define Q1319	 	10567

	%define N1321	 	1321
	%define Q1321	 	10597

	%define N1327	 	1327
	%define Q1327	 	10613

	%define N1361	 	1361
	%define Q1361	 	10957

	%define N1373	 	1373
	%define Q1373	 	11057

	%define N1381	 	1381
	%define Q1381	 	11059

	%define N1399	 	1399
	%define Q1399	 	11213

	%define N1409	 	1409
	%define Q1409	 	11299

	%define N1423	 	1423
	%define Q1423	 	11383

	%define N1427	 	1427
	%define Q1427	 	11437

	%define N1429	 	1429
	%define Q1429	 	11443
	
	
	%if N == 1301
		%define N_   N1301
		%define Q_   Q1301
	%endif
		
	%if N == 1303
		%define N_   N1303
		%define Q_   Q1303
	%endif
		
	%if N == 1307
		%define N_   N1307
		%define Q_   Q1307
	%endif
		
	%if N == 1319
		%define N_   N1319
		%define Q_   Q1319
	%endif
		
	%if N == 1321
		%define N_   N1321
		%define Q_   Q1321
	%endif
	%if N == 1321
		%define N_   N1321
		%define Q_   Q1319
	%endif
		
	%if N == 1327
		%define N_   N1327
		%define Q_   Q1327
	%endif
		
	%if N == 1361
		%define N_   N1361
		%define Q_   Q1361
	%endif

	
	%if N == 1373
		%define N_   N1373
		%define Q_   Q1373
	%endif
	
	%if N == 1381
		%define N_   N1381
		%define Q_   Q1381
	%endif
	
	%if N == 1399
		%define N_   N1399
		%define Q_   Q1399
	%endif
	
	%if N == 1409
		%define N_   N1409
		%define Q_   Q1409
	%endif
		
	%if N == 1423
		%define N_   N1423
		%define Q_   Q1423
	%endif
		
	%if N == 1427
		%define N_   N1427
		%define Q_   Q1427
	%endif
	
	%if N == 1429
		%define N_   N1429
		%define Q_   Q1429
	%endif
	
%endif
	
%endif




 %define Q_2	 		(Q_/2)
 %define N32_	  ((N_ + 31)/32)
 %define N32	 	(N32_ * 32)	
 %define N32N_	  	(N32 -N_)	
 %define N8_	 	((N_+7)/8)
 %define N8		 	(N8_ * 8)
 %define N16_	 	((N_+15)/16)
 %define N16	  	(N16_ * 16)
 %define N348	 	((N_ + 3) / 4 * 8)

EXTERN q256_16
EXTERN q256_2_16
EXTERN _0_16
EXTERN	maska256_16


;KEYS_STRUCI16_ASM STRUCT
;	h				dw	(N16 + AVX_LEN / 2 )				dup (?)
;	res_internal	dw	(AVX_LEN / 2 * 16 + N16 * 2 + 16 )	dup (?)
;	res				dw	(N16 )							dup (?)
;	onesCount		dw	?
;	minusonesCount	dw	?
;	ones			dw	N_ dup (?)
;	;signed char temp[32 - sizeof(IITR3_16) % 32];
;	temp			db	(32 - ((2 + 2 + 2 * (2 * N_/3) mod 32))) dup (?)
;KEYS_STRUCI16_ASM	ends

struc KEYS_STRUCI16_ASM 
    .h              : resw (N16 + AVX_LEN/2)
    .res_internal   : resw (AVX_LEN/2 * 16 + N16*2+16)
    .res            : resw (N16)
    .onesCount      : resw (1)
    .minusonesCount : resw (1)
    .ones           : resw (2 * N_ / 3 + 1)
    .temp           : resb (32 - (2+2+ 2*(2 * N_ / 3 + 1)) % 32)
endstruc

;typedef struct
;{
;	signed short *h, *h_; 
;	__m256i*predcalc, *predcalc_;
;
;}THREAD_CONST_PARAM_STRUCI16, *PTHREAD_CONST_PARAM_STRUCI16;

;THREAD_CONST_PARAM_STRUCI16_ASM STRUCT
;h			dq		?
;h_			dq		?
;predcalc	dq		?
;predcalc_	dq		?
;THREAD_CONST_PARAM_STRUCI16_ASM	ends

struc THREAD_CONST_PARAM_STRUCI16_ASM 
    .h         : resq 1
    .h_        : resq 1
    .predcalc  : resq 1
    .predcalc_ : resq 1
endstruc

;typedef struct
;{
;	__m256i *res;
;	unsigned short *plus, *minus;
;	unsigned short plus_count, minus_count;
;}THREAD_PARAM_STRUCI16, *PTHREAD_PARAM_STRUCI16;

;THREAD_PARAM_STRUCI16_ASM	STRUCT
;res			dq		?
;plus		dq		?
;minus		dq		?
;plus_count	dw		?
;minus_count	dw		?
;THREAD_PARAM_STRUCI16_ASM ends


struc THREAD_PARAM_STRUCI16_ASM
    .res         : resq 1
    .plus        : resq 1
    .minus       : resq 1
    .plus_count  : resw 1
    .minus_count : resw 1
endstruc

%if 0
typedef struct
{
	short  h[N16 + AVX_LEN / 2];	// 0, 768 * 2 = 1536  
	short  internal_result[16 + N16 * 2 + 32];	// 7680, 768 * 2 = 1536  
	short  result1[N16 + 16];	// 1536, 3072 
	NTRUPrimePolinomStruct3 r3;
	/*short  f1plus[D1], f1minus[D1];
	short  f2plus[D2], f2minus[D2];
	short  f3plus[D3], f3minus[D3];*/

	signed char temp[32 - (sizeof(NTRUPrimePolinomStruct3) % 32)];


}KEY3_CACHE_STRUCT, *PKEY3_CACHE_STRUCT;
%endif
%if F1F2F3 == 1 
;KEY3_CACHE_STRUCT_ASM	STRUCT
;	;h				dw	(N16 + AVX_LEN / 2) dup	?
;	;result1			dw	(N16 + AVX_LEN / 2) dup	?
;	f1plus			dw	(D1_)	dup (?)
;	f1minus			dw	(D1_)	dup (?)
;	f2plus			dw	(D2_)	dup (?)
;	f2minus			dw	(D2_)	dup (?)
;	f3plus			dw	(D3_)	dup (?)
;	f3minus			dw	(D3_)	dup (?)
;	temp			db	(32 - 4 * (D1_ + D2_ + D3_) mod	32) dup (?)
;KEY3_CACHE_STRUCT_ASM	ENDS

struc KEY3_CACHE_STRUCT
    .h          : resw (N16 + AVX_LEN/2)
    .internal_result : resw (16 + N16 * 2 + 32)
    .result1    :  resw (N16 + 16)
    .f1plus     : resw (D1_)
    .f1minus    : resw (D1_)
    .f2plus     : resw (D2_)
    .f2minus    : resw (D2_)
    .f3plus     : resw (D3_)
    .f3minus    : resw (D3_)
    .temp       : resb (32 - 4*(D1_+D2_+D3_) % 32)
endstruc

%endif






