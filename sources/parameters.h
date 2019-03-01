#ifndef parameters_h
#define parameters_h

#define OID	"\x00\x00\x01"

//Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define K  256
//#define K  384
//#define K  512

//#define F1F2F3	1
#define F1F2F3	0
//Change macroses!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



#if F1F2F3 == 1



	#if K ==  256
		#define N	787
	#endif

	#if K ==  384
		#define N	1019
	#endif

	#if K == 512
		#define	N	1301
	#endif
#else
	#if K == 256
		#define	N	761
	#endif
	#if K == 384
		#define N 1031
	#endif
	#if K == 512
		#define	N	1301
	#endif
#endif
#if F1F2F3 == 1
	#define N787		787
	#define Q787		7307
	#define T787		262
	#define D1_787		12
	#define D2_787		12
	#define D3_787		15
#define DM_787			219

	#define N1019		1019
	#define Q1019		8867
	#define T1019		339
	#define D1_1019		13
	#define D2_1019		13
	#define D3_1019		31
#define DM_1019			290

	#define N1301		1301
	#define Q1301		11959
	#define T1301		433
	#define D1_1301		15
	#define D2_1301		15
	#define D3_1301		48
#define DM_1301		377
	
	#define N1409		1409
	#define Q1409		13327
	#define T1409		469
	#define D1_1409		16
	#define D2_1409		16
	#define D3_1409		43
#define DM_1409		411
	
	#if N == 787
		#define N_     N787
		#define Q_     Q787
		#define T_     T787
		#define D1_     D1_787
		#define D2_     D2_787
		#define D3_     D3_787
#define DM_     DM_787
	#endif

	#if N == 1019
		#define N_     N1019
		#define Q_     Q1019
		#define T_     T1019
		#define D1_     D1_1019
		#define D2_     D2_1019
		#define D3_     D3_1019
#define DM_     DM_1019
	#endif

	#if N == 1301
		#define N_     N1301
		#define Q_     Q1301
		#define T_     T1301
		#define D1_     D1_1301
		#define D2_     D2_1301
		#define D3_     D3_1301
#define DM_     DM_1301
	#endif


	#if N == 1409
		#define N_     N1409
		#define Q_     Q1409
		#define T_     T1409
		#define D1_     D1_1409
		#define D2_     D2_1409
		#define D3_     D3_1409
#define DM_     DM_1409
	#endif

#else
#if K == 512
	#define N1301		1301
	#define N1303		1303
	#define N1307		1307
	#define N1319		1319
	#define N1321		1321
	#define N1327		1327
	#define N1361		1361
	#define N1373		1373
	#define N1381		1381
	#define N1399		1399
	#define N1409		1409
	#define N1423		1423
	#define N1427		1427
	#define N1429		1429

	#define T1301		217
	#define T1303		217
	#define T1307		218
	#define T1319		220
	#define T1321		220
	#define T1327		221
	#define T1361		227
	#define T1373		229
	#define T1381		230
	#define T1399		233
	#define T1409		235
	#define T1423		237
	#define T1427		238
	#define T1429		238

	#define Q1301		10427
	#define Q1303		10429
	#define Q1307		10499
	#define Q1319		10567
	#define Q1321		10597
	#define Q1327		10613
	#define Q1361		10957
	#define Q1373		11057
	#define Q1381		11059
	#define Q1399		11213
	#define Q1409		11299
	#define Q1423		11383
	#define Q1427		11437
	#define Q1429		11443

	#if N == 1301
		#define N_	N1301
		#define T_	T1301	
		#define Q_	Q1301	
	#endif

	#if N == 1303
		#define N_	N1303
		#define T_	T1303	
		#define Q_	Q1303	
	#endif
	
	#if N == 1307
		#define N_	N1307
		#define T_	T1307	
		#define Q_	Q1307	
	#endif

	#if N == 1319
		#define N_	N1319
		#define T_	T1319	
		#define Q_	Q1319	
	#endif

	#if N == 1321
		#define N_	N1321
		#define T_	T1321	
		#define Q_	Q1321	
	#endif

	#if N == 1327
		#define N_	N1327
		#define T_	T1327	
		#define Q_	Q1327	
	#endif

	#if N == 1361
		#define N_	N1361
		#define T_	T1361	
		#define Q_	Q1361	
	#endif

	#if N == 1373
		#define N_	N1373
		#define T_	T1373	
		#define Q_	Q1373	
	#endif

	#if N == 1381
		#define N_	N1381
		#define T_	T1381	
		#define Q_	Q1381	
	#endif
	#if N == 1399
		#define N_	N1399
		#define T_	T1399	
		#define Q_	Q1399	
	#endif
	#if N == 1409
		#define N_	N1409
		#define T_	T1409	
		#define Q_	Q1409	
	#endif

	#if N == 1423
		#define N_	N1423
		#define T_	T1423	
		#define Q_	Q1423	
	#endif
//1427
	#if N == 1427
		#define N_	N1427
		#define T_	T1427	
		#define Q_	Q1427	
	#endif

	#if N == 1429
		#define N_	N1429
		#define T_	T1429	
		#define Q_	Q1429	
	#endif


#endif

#if K==384
#define N1031	1031
#define Q1031	8297
#define T1031	172
#if N == 1031
#define N_	N1031
#define T_	T1031	
#define Q_	Q1031	
#endif
#endif

#if K==256

	#define N761	761
	#define Q761	4591
	#define T761	143


	#define N881	881
	#define Q881	7673
	#define T881	159

	#define N883	883
	#define Q883	8089
	#define T883	168

	#define N907	907
	#define Q907	7727
	#define T907	160

	#define N953	953
	#define Q953	6343
	#define T953	132

	#define N967	967
	#define Q967	8243
	#define T967	171

	#define N971	971
	#define Q971	4871
	#define T971	101

	#define N977	977
	#define Q977	5783
	#define T977	120

	#define N991	991
	#define Q991	9349
	#define T991	194

	#define N997	997
	#define Q997	5393
	#define T997	112

	#define N1013	1013
	#define Q1013	7177
	#define T1013	149

	#define N1019	1019
	#define Q1019	6691
	#define T1019	139

	#define N1021	1021
	#define Q1021	5393
	#define T1021	112

#if N == 761
#define N_	N761
#define T_	T761	
#define Q_	Q761	
#endif

#if N == 881
#define N_	N881
#define T_	T881	
#define Q_	Q881	
#endif

#if N == 883
#define N_	N883
#define T_	T883	
#define Q_	Q883	
#endif

#if N == 907
#define N_	N907
#define T_	T907	
#define Q_	Q907	
#endif


#if N == 953
#define N_	N953
#define T_	T953	
#define Q_	Q953	
#endif

#if N == 953
#define N_	N967
#define T_	T967	
#define Q_	Q967	
#endif

#if N == 971
#define N_	N971
#define T_	T971	
#define Q_	Q971	
#endif

#if N == 977
#define N_	N977
#define T_	T977	
#define Q_	Q977	
#endif

#if N == 991
#define N_	N991
#define T_	T991	
#define Q_	Q991	
#endif

#if N == 997
#define N_	N997
#define T_	T997	
#define Q_	Q997	
#endif

#if N == 1013
#define N_	N1013
#define T_	T1013	
#define Q_	Q1013	
#endif

#if N == 1019
#define N_	N1019
#define T_	T1019	
#define Q_	Q1019	
#endif

#if N == 1021
#define N_	N1021
#define T_	T1021	
#define Q_	Q1021	
#endif

#endif
#endif

#define Q_2		(Q_/2)
#define N32_	((N_ + 31)/32)
#define N32		(N32_ * 32)	
#define N32_N		(N32 -N_)	
#define N8_		((N_+7)/8)
#define N8		(N8_ * 8)
#define N16_	((N_+15)/16)
#define N16		(N16_ * 16)
#define N348	((N_ + 3) / 4 * 8)


#ifdef _MSC_VER
#define ALLOCA(size) _alloca(size)

#else
#define ALLOCA(size) alloca(size)

#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#define __rtdc
#endif

#endif


