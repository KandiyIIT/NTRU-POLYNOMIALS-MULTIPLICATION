
AVX_LEN =		32
; Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
K =  256
;K = 384
;K = 512

;F1F2F3 = 1
F1F2F3 = 0
; Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

if F1F2F3 eq 1
	if K eq  256
		N = 787
	endif
	if K eq  384
		N = 1019
	endif
	if K eq 512
		N = 1301
	endif
else
	if K eq  256
		N = 881
	endif
	if K eq  384
		N = 1031
	endif
	if K eq  512
		N = 1301
	endif
endif

if F1F2F3 eq 1
	N787 = 787
	Q787 = 7307
	D1_787 = 12
	D2_787 = 12
	D3_787 = 15
	N1019 = 1019
	Q1019 = 8867
	D1_1019 = 13
	D2_1019 = 13
	D3_1019 = 31
	N1301 = 1301
	Q1301 = 11959
	D1_1301 = 15
	D2_1301 = 15
	D3_1301 = 48

	N1409 = 1409
	Q1409 = 13327
	D1_1409 = 16
	D2_1409 = 16
	D3_1409 = 43
	if N eq 787
		N_ = N787
		Q_ = Q787
		D1_ = D1_787
		D2_ = D2_787
		D3_ = D3_787

	endif
	if N eq 1019
		N_ = N1019
		Q_ = Q1019
		D1_ = D1_1019
		D2_ = D2_1019
		D3_ = D3_1019
	endif
	if N eq 1301
		N_ = N1301
		Q_ = Q1301
		D1_ = D1_1301
		D2_ = D2_1301
		D3_ = D3_1301
	endif
	if N eq 1409
		N_ = N1409
		Q_ = Q1409
		D1_ = D1_1409
		D2_ = D2_1409
		D3_ = D3_1409
	endif
else
if K eq 256
	N761	=	761
	Q761	=	4591
		
	N881	=	881
	Q881	=	7673
	
	N883	=	883
	Q883	=	8089
 
	N907	=	907
	Q907	=	7727
 
	N953	=	953
	Q953	=	6343
 
	N967	=	967
	Q967	=	8243
 
	N971	=	971
	Q971	=	4871
	
	N977	=	977
	Q977	=	5783
 
	N991	=	991
	Q991	=	9349
 
	N997	=	997
	Q997	=	5393
		
	N1013	=	1013
	Q1013	=	7177
 

	N1019	=	1019
	Q1019	=	6691
 
	N1021	=	1021
	Q1021	=	5393

	if N eq 761
		N_ = N761
		Q_ = Q761
	endif

	if N eq 881
		N_ = N881
		Q_ = Q881
	endif

	if N eq 883
		N_ = N883
		Q_ = Q883
	endif
	if N eq 907
		N_ = N907
		Q_ = Q907
	endif
	if N eq 953
		N_ = N953
		Q_ = Q953
	endif
	if N eq 967
		N_ = N967
		Q_ = Q967
	endif
	if N eq 971
		N_ = N971
		Q_ = Q971
	endif
	if N eq 977
		N_ = N977
		Q_ = Q977
	endif
	if N eq 991
		N_ = N991
		Q_ = Q991
	endif
	if N eq 997
		N_ = N997
		Q_ = Q997
	endif
	
	if N eq 1013
		N_ = N1013
		Q_ = Q1013
	endif

	if N eq 1019
		N_ = N1019
		Q_ = Q1019
	endif
	if N eq 1021
		N_ = N1021
		Q_ = Q1021
	endif
	
endif

if K eq 384
	N1031  = 1031
	Q1031  = 8297
	if N eq 1031
		N_ = N1031
		Q_ = Q1031
	endif
endif 

if K eq 512


	N1301	=	1301
	Q1301	=	10427

	N1303	=	1303
	Q1303	=	10429

	N1307	=	1307
	Q1307	=	10499

	N1319	=	1319
	Q1319	=	10567

	N1321	=	1321
	Q1321	=	10597

	N1327	=	1327
	Q1327	=	10613

	N1361	=	1361
	Q1361	=	10957

	N1373	=	1373
	Q1373	=	11057

	N1381	=	1381
	Q1381	=	11059

	N1399	=	1399
	Q1399	=	11213

	N1409	=	1409
	Q1409	=	11299

	N1423	=	1423
	Q1423	=	11383

	N1427	=	1427
	Q1427	=	11437

	N1429	=	1429
	Q1429	=	11443
	
	
	if N eq 1301
		N_ = N1301
		Q_ = Q1301
	endif
		
	if N eq 1303
		N_ = N1303
		Q_ = Q1303
	endif
		
	if N eq 1307
		N_ = N1307
		Q_ = Q1307
	endif
		
	if N eq 1319
		N_ = N1319
		Q_ = Q1319
	endif
		
	if N eq 1321
		N_ = N1321
		Q_ = Q1321
	endif
	if N eq 1321
		N_ = N1321
		Q_ = Q1319
	endif
		
	if N eq 1327
		N_ = N1327
		Q_ = Q1327
	endif
		
	if N eq 1361
		N_ = N1361
		Q_ = Q1361
	endif

	
	if N eq 1373
		N_ = N1373
		Q_ = Q1373
	endif
	
	if N eq 1381
		N_ = N1381
		Q_ = Q1381
	endif
	
	if N eq 1399
		N_ = N1399
		Q_ = Q1399
	endif
	
	if N eq 1409
		N_ = N1409
		Q_ = Q1409
	endif
		
	if N eq 1423
		N_ = N1423
		Q_ = Q1423
	endif
		
	if N eq 1427
		N_ = N1427
		Q_ = Q1427
	endif
	
	if N eq 1429
		N_ = N1429
		Q_ = Q1429
	endif
	
endif
	
endif




 Q_2	=		(Q_/2)
 N32_	= ((N_ + 31)/32)
 N32	=	(N32_ * 32)	
 N32N_	= 	(N32 -N_)	
 N8_	=	((N_+7)/8)
 N8		=	(N8_ * 8)
 N16_	=	((N_+15)/16)
 N16	= 	(N16_ * 16)
 N348	=	((N_ + 3) / 4 * 8)

EXTERN q256_16: YMMWORD
EXTERN q256_2_16:  YMMWORD
EXTERN _0_16: YMMWORD
EXTERN	maska256_16: YMMWORD


KEYS_STRUCI16_ASM STRUCT
	h				dw	(N16 + AVX_LEN / 2 )				dup (?)
	res_internal	dw	(AVX_LEN / 2 * 16 + N16 * 2 + 16 )	dup (?)
	res				dw	(N16 )							dup (?)
	onesCount		dw	?
	minusonesCount	dw	?
	ones			dw	N_ dup (?)
	;signed char temp[32 - sizeof(IITR3_16) % 32];
	temp			db	(32 - ((2 + 2 + 2 * (2 * N_/3) mod 32))) dup (?)
KEYS_STRUCI16_ASM	ends

;typedef struct
;{
;	signed short *h, *h_; 
;	__m256i*predcalc, *predcalc_;
;
;}THREAD_CONST_PARAM_STRUCI16, *PTHREAD_CONST_PARAM_STRUCI16;

THREAD_CONST_PARAM_STRUCI16_ASM STRUCT
h			dq		?
h_			dq		?
predcalc	dq		?
predcalc_	dq		?
THREAD_CONST_PARAM_STRUCI16_ASM	ends

;typedef struct
;{
;	__m256i *res;
;	unsigned short *plus, *minus;
;	unsigned short plus_count, minus_count;
;}THREAD_PARAM_STRUCI16, *PTHREAD_PARAM_STRUCI16;

THREAD_PARAM_STRUCI16_ASM	STRUCT
res			dq		?
plus		dq		?
minus		dq		?
plus_count	dw		?
minus_count	dw		?
THREAD_PARAM_STRUCI16_ASM ends

if 0
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


}F1F2F3_KEYS_STRUCI, *PF1F2F3_KEYS_STRUCI;
endif
if F1F2F3 eq 1 
F1F2F3_KEYS_STRUCI_ASM	STRUCT
	;h				dw	(N16 + AVX_LEN / 2) dup	?
	;result1			dw	(N16 + AVX_LEN / 2) dup	?
	f1plus			dw	(D1_)	dup (?)
	f1minus			dw	(D1_)	dup (?)
	f2plus			dw	(D2_)	dup (?)
	f2minus			dw	(D2_)	dup (?)
	f3plus			dw	(D3_)	dup (?)
	f3minus			dw	(D3_)	dup (?)
	temp			db	(32 - 4 * (D1_ + D2_ + D3_) mod	32) dup (?)
F1F2F3_KEYS_STRUCI_ASM	ENDS
endif






