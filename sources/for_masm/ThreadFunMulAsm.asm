
include macroses.inc


_TEXT    SEGMENT
if 0
thread_mul_asm	PROC
push rbp
mov		rbp, rsp
and		rbp, 31

add		rbp, 64 + 16 * 16 + (16 + N16 * 2 + 32) * 2
sub		rsp, rbp

mov	r11, rsp
add	r11, 64

;  save sse registers

movaps      xmmword ptr [R11 + 00H],xmm5
movaps      xmmword ptr [R11 + 10H],xmm6
movaps      xmmword ptr [R11 + 20H],xmm7
movaps      xmmword ptr [R11 + 30H],xmm8
movaps      xmmword ptr [R11 + 40H],xmm9





; save registers RBX, RBP, RDI, RSI, RSP, R12, R13, R14, and R15.
push	rbx
push	rsi
push	rdi
push	r12
push	r13
push	r14
push	r15


; signed short *thread_rh = temp + 16; //rh_[thread];
mov		r13, rcx;
mov		r14, rdx
lea		r12, [r11 + 256 + 32] ; Local area address (rh_[thread])

; memset(thread_rh, 0, N16 * 2 * sizeof(thread_rh[0]) + 32);
mov	rdi, r12
xor	eax, eax
mov	rcx, (N16 * 2 * 2 + 32) / 4
cld
rep	stosd

; for (i = 0; i < thread_nums_minus; i++)

xor	rax, rax
xor	rbx, rbx
xor	rdx, rdx
if 1
mov	cx, [R14].THREAD_PARAM_STRUCI16_ASM.minus_count
else
mov	cx, 1
endif
; k = thread_pk_minus[i];

mov	rsi, [R14].THREAD_PARAM_STRUCI16_ASM.minus
;mov	rsi, [rsi]
mov	r15, [R13].THREAD_CONST_PARAM_STRUCI16_ASM.predcalc
mov	r10, [R13].THREAD_CONST_PARAM_STRUCI16_ASM.h
VPXOR		ymm12, ymm12, ymm12; 0
VMOVDQA	ymm13, ymmword ptr [q256_16]; Q
;mov	r15, r15 



for_minus_label:
mov	ax, [rsi]



;line = k % 16;
mov	bx, ax
and	bx, 15
mov	dx, bx
sub	dx, 16
neg	dx
lea	r9, [r10 + rdx * 2]
shl	bx, 5
;col = k >> 4
mov	dx, ax
shr	dx, 4
shl	dx, 5
; ck256 = rh256 + col;
lea	rdi, [r12 + rdx]; 
;r0 = _mm256_sub_epi16(ck256[0], thread_coeffs[line]);
VMOVDQA	ymm0, ymmword ptr [rdi]
VPSUBW	ymm0, ymm0, ymmword ptr [r15 + rbx]
;_mm256_store_si256(ck256,
;			_mm256_add_epi16(
;			r0,
;			_mm256_and_si256(
;			_mm256_cmpgt_epi16(r12, r0), r13)));
; _mm256_cmpgt_epi16(r12, r0)
VPCMPGTW	ymm1, ymm12, ymm0
;_mm256_and_si256
VPAND	ymm1, ymm1, ymm13
; _mm256_add_epi16
VPADDW	ymm0, ymm0, ymm1
VMOVDQA	ymmword ptr [rdi], ymm0
;cur_h256 = (__m256i*)(h - line);

;		k = 1;
lea	rdi, [rdi + 32];
COMMENT @
for (j = 1; j <= N16_ / 8; j++)
		{
			r0 = _mm256_sub_epi16(ck256[k], _mm256_lddqu_si256(cur_h256 + k));
			r1 = _mm256_sub_epi16(ck256[k + 1], _mm256_lddqu_si256(cur_h256 + k + 1));
			r2 = _mm256_sub_epi16(ck256[k + 2], _mm256_lddqu_si256(cur_h256 + k + 2));
			r3 = _mm256_sub_epi16(ck256[k + 3], _mm256_lddqu_si256(cur_h256 + k + 3));
			r4 = _mm256_sub_epi16(ck256[k + 4], _mm256_lddqu_si256(cur_h256 + k + 4));
			r5 = _mm256_sub_epi16(ck256[k + 5], _mm256_lddqu_si256(cur_h256 + k + 5));
			r6 = _mm256_sub_epi16(ck256[k + 6], _mm256_lddqu_si256(cur_h256 + k + 6));
			r7 = _mm256_sub_epi16(ck256[k + 7], _mm256_lddqu_si256(cur_h256 + k + 7));

			_mm256_store_si256(ck256 + k,
				_mm256_add_epi16(r0,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r0), r13)));
			_mm256_store_si256(ck256 + k + 1,
				_mm256_add_epi16(r1,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r1), r13)));
			_mm256_store_si256(ck256 + k + 2,
				_mm256_add_epi16(r2,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r2), r13)));
			_mm256_store_si256(ck256 + k + 3,
				_mm256_add_epi16(r3,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r3), r13)));
			_mm256_store_si256(ck256 + k + 4,
				_mm256_add_epi16(r4,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r4), r13)));
			_mm256_store_si256(ck256 + k + 5,
				_mm256_add_epi16(r5,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r5), r13)));
			_mm256_store_si256(ck256 + k + 6,
				_mm256_add_epi16(r6,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r6), r13)));
			_mm256_store_si256(ck256 + k + 7,
				_mm256_add_epi16(r7,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r7), r13)));

			k += 8;
		}
 @
 ;if  0
 REPT N16_ / 8
 ;else
 ;push	rcx
 ;mov	ecx, N16_ / 8
 ;for1:
 ;endif
 ;r0 = _mm256_sub_epi16(ck256[k], _mm256_lddqu_si256(cur_h256 + k));
 
 VMOVDQA	ymm0, ymmword ptr[rdi]
 VMOVDQA	ymm1, ymmword ptr[rdi + 32]
 VMOVDQA	ymm2, ymmword ptr[rdi + 64]
 VMOVDQA	ymm3, ymmword ptr[rdi + 96]
 VMOVDQA	ymm4, ymmword ptr[rdi + 128]
 VMOVDQA	ymm5, ymmword ptr[rdi + 160]
 VMOVDQA	ymm6, ymmword ptr[rdi + 192]
 VMOVDQA	ymm7, ymmword ptr[rdi + 224]
 
 vlddqu		ymm8, ymmword ptr [r9]
 vlddqu		ymm9, ymmword ptr [r9 + 32]
 vlddqu		ymm10, ymmword ptr [r9 + 64]
 vlddqu		ymm11, ymmword ptr [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11

 vlddqu		ymm8, ymmword ptr [r9 + 128]
 vlddqu		ymm9, ymmword ptr [r9 + 160]
 vlddqu		ymm10, ymmword ptr [r9 + 192]
 vlddqu		ymm11, ymmword ptr [r9 + 224]
 
 VPSUBW		ymm4, ymm4, ymm8
 VPSUBW		ymm5, ymm5, ymm9
 VPSUBW		ymm6, ymm6, ymm10
 VPSUBW		ymm7, ymm7, ymm11
 ;_mm256_store_si256(ck256 + k,
	;			_mm256_add_epi16(r0,
	;			_mm256_and_si256(
	;			_mm256_cmpgt_epi16(r12, r0), r13)));
VPCMPGTW	ymm8, ymm12, ymm0
VPCMPGTW	ymm9, ymm12, ymm1
VPCMPGTW	ymm10, ymm12, ymm2
VPCMPGTW	ymm11, ymm12, ymm3

VPAND	ymm8, ymm8, ymm13
VPAND	ymm9, ymm9, ymm13
VPAND	ymm10, ymm10, ymm13
VPAND	ymm11, ymm11, ymm13

VPADDW	ymm0, ymm0, ymm8
VPADDW	ymm1, ymm1, ymm9
VPADDW	ymm2, ymm2, ymm10
VPADDW	ymm3, ymm3, ymm11

VPCMPGTW	ymm8, ymm12, ymm4
VPCMPGTW	ymm9, ymm12, ymm5
VPCMPGTW	ymm10, ymm12, ymm6
VPCMPGTW	ymm11, ymm12, ymm7

VPAND	ymm8, ymm8, ymm13
VPAND	ymm9, ymm9, ymm13
VPAND	ymm10, ymm10, ymm13
VPAND	ymm11, ymm11, ymm13

VPADDW	ymm4, ymm4, ymm8
VPADDW	ymm5, ymm5, ymm9
VPADDW	ymm6, ymm6, ymm10
VPADDW	ymm7, ymm7, ymm11

VMOVDQA	ymmword ptr[rdi], ymm0
VMOVDQA	ymmword ptr[rdi + 32], ymm1
VMOVDQA	ymmword ptr[rdi + 64], ymm2
VMOVDQA	ymmword ptr[rdi + 96], ymm3
VMOVDQA	ymmword ptr[rdi + 128], ymm4
VMOVDQA	ymmword ptr[rdi + 160], ymm5
VMOVDQA	ymmword ptr[rdi + 192], ymm6
VMOVDQA	ymmword ptr[rdi + 224], ymm7
lea	rdi, [rdi + 256]
lea	r9, [r9 + 256]
;if 0
endm
;else
;dec	ecx
;jnz	for1
;pop rcx
;endif
rept	N16_ mod 8
VMOVDQA	ymm0, ymmword ptr[rdi]
vlddqu		ymm8, ymmword ptr [r9]
VPSUBW		ymm0, ymm0, ymm8
VPCMPGTW	ymm8, ymm12, ymm0
VPAND	ymm8, ymm8, ymm13
VPADDW	ymm0, ymm0, ymm8
VMOVDQA	ymmword ptr[rdi], ymm0
lea	rdi, [rdi + 32]
lea	r9, [r9 + 32]
endm

 lea	rsi, [rsi + 2]
 
 dec	cx;
 jnz	for_minus_label
 

if 1
; plus
mov	rdi, r12
mov	cx, [R14].THREAD_PARAM_STRUCI16_ASM.plus_count
; k = thread_pk_minus[i];
mov	rsi, [R14].THREAD_PARAM_STRUCI16_ASM.plus
;mov	rsi, [rsi]
mov	r15, [R13].THREAD_CONST_PARAM_STRUCI16_ASM.predcalc_
mov	r10, [R13].THREAD_CONST_PARAM_STRUCI16_ASM.h_
; for (i = 0; i < thread_nums_plus; i++)

for_plus_label:
;k = thread_pk_plus[i];
mov	ax, [rsi]
;		line = k % 16;
mov	bx, ax
and	bx, 15
mov	dx, bx
sub	dx, 16
neg	dx
lea	r9, [r10 + rdx * 2]
shl	bx, 5

;col = k >> 4;
mov	dx, ax
shr	dx, 4
shl	dx, 5
		;ck256 = rh256 + col;
lea	rdi, [r12 + rdx]; 
;r0 = _mm256_sub_epi16(ck256[0], thread_coeffs[line]);
VMOVDQA	ymm0, ymmword ptr [rdi]
VPSUBW	ymm0, ymm0, ymmword ptr [r15 + rbx]
;_mm256_store_si256(ck256,
;			_mm256_add_epi16(r0,
;			_mm256_and_si256(
;			_mm256_cmpgt_epi16(r12, r0), r13)));

 VPCMPGTW	ymm8, ymm12, ymm0
 VPAND		ymm8, ymm8, ymm13
 VPADDW		ymm0, ymm0, ymm8
 VMOVDQA	ymmword ptr [rdi], ymm0
 lea		rdi, [rdi + 32]
 COMMENT	@
 for (j = 1; j <= N16_ / 8; j++)
		{
			r0 = _mm256_sub_epi16(ck256[k], _mm256_lddqu_si256(cur_h256 + k));
			r1 = _mm256_sub_epi16(ck256[k + 1], _mm256_lddqu_si256(cur_h256 + k + 1));
			r2 = _mm256_sub_epi16(ck256[k + 2], _mm256_lddqu_si256(cur_h256 + k + 2));
			r3 = _mm256_sub_epi16(ck256[k + 3], _mm256_lddqu_si256(cur_h256 + k + 3));
			r4 = _mm256_sub_epi16(ck256[k + 4], _mm256_lddqu_si256(cur_h256 + k + 4));
			r5 = _mm256_sub_epi16(ck256[k + 5], _mm256_lddqu_si256(cur_h256 + k + 5));
			r6 = _mm256_sub_epi16(ck256[k + 6], _mm256_lddqu_si256(cur_h256 + k + 6));
			r7 = _mm256_sub_epi16(ck256[k + 7], _mm256_lddqu_si256(cur_h256 + k + 7));

			_mm256_store_si256(ck256 + k,
				_mm256_add_epi16(r0,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r0), r13)));
			_mm256_store_si256(ck256 + k + 1,
				_mm256_add_epi16(r1,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r1), r13)));

			_mm256_store_si256(ck256 + k + 2,
				_mm256_add_epi16(r2,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r2), r13)));

			_mm256_store_si256(ck256 + k + 3,
				_mm256_add_epi16(r3,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r3), r13)));

			_mm256_store_si256(ck256 + k + 4,
				_mm256_add_epi16(r4,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r4), r13)));

			_mm256_store_si256(ck256 + k + 5,
				_mm256_add_epi16(r5,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r5), r13)));

			_mm256_store_si256(ck256 + k + 6,
				_mm256_add_epi16(r6,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r6), r13)));

			_mm256_store_si256(ck256 + k + 7,
				_mm256_add_epi16(r7,
				_mm256_and_si256(
				_mm256_cmpgt_epi16(r12, r7), r13)));


			k += 8;
		}
 @
 ;for (j = 1; j <= N16_ / 8; j++)
 rept	N16_ / 8
	; r0 = _mm256_sub_epi16(ck256[k], _mm256_lddqu_si256(cur_h256 + k));
	VMOVDQA	ymm0, ymmword ptr[rdi]
 VMOVDQA	ymm1, ymmword ptr[rdi + 32]
 VMOVDQA	ymm2, ymmword ptr[rdi + 64]
 VMOVDQA	ymm3, ymmword ptr[rdi + 96]
 VMOVDQA	ymm4, ymmword ptr[rdi + 128]
 VMOVDQA	ymm5, ymmword ptr[rdi + 160]
 VMOVDQA	ymm6, ymmword ptr[rdi + 192]
 VMOVDQA	ymm7, ymmword ptr[rdi + 224]
 
 vlddqu		ymm8, ymmword ptr [r9]
 vlddqu		ymm9, ymmword ptr [r9 + 32]
 vlddqu		ymm10, ymmword ptr [r9 + 64]
 vlddqu		ymm11, ymmword ptr [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11

 vlddqu		ymm8, ymmword ptr [r9 + 128]
 vlddqu		ymm9, ymmword ptr [r9 + 160]
 vlddqu		ymm10, ymmword ptr [r9 + 192]
 vlddqu		ymm11, ymmword ptr [r9 + 224]
 
 VPSUBW		ymm4, ymm4, ymm8
 VPSUBW		ymm5, ymm5, ymm9
 VPSUBW		ymm6, ymm6, ymm10
 VPSUBW		ymm7, ymm7, ymm11
 ;_mm256_store_si256(ck256 + k,
	;			_mm256_add_epi16(r0,
	;			_mm256_and_si256(
	;			_mm256_cmpgt_epi16(r12, r0), r13)));
VPCMPGTW	ymm8, ymm12, ymm0
VPCMPGTW	ymm9, ymm12, ymm1
VPCMPGTW	ymm10, ymm12, ymm2
VPCMPGTW	ymm11, ymm12, ymm3

VPAND	ymm8, ymm8, ymm13
VPAND	ymm9, ymm9, ymm13
VPAND	ymm10, ymm10, ymm13
VPAND	ymm11, ymm11, ymm13

VPADDW	ymm0, ymm0, ymm8
VPADDW	ymm1, ymm1, ymm9
VPADDW	ymm2, ymm2, ymm10
VPADDW	ymm3, ymm3, ymm11

VPCMPGTW	ymm8, ymm12, ymm4
VPCMPGTW	ymm9, ymm12, ymm5
VPCMPGTW	ymm10, ymm12, ymm6
VPCMPGTW	ymm11, ymm12, ymm7

VPAND	ymm8, ymm8, ymm13
VPAND	ymm9, ymm9, ymm13
VPAND	ymm10, ymm10, ymm13
VPAND	ymm11, ymm11, ymm13

VPADDW	ymm4, ymm4, ymm8
VPADDW	ymm5, ymm5, ymm9
VPADDW	ymm6, ymm6, ymm10
VPADDW	ymm7, ymm7, ymm11

VMOVDQA	ymmword ptr[rdi], ymm0
VMOVDQA	ymmword ptr[rdi + 32], ymm1
VMOVDQA	ymmword ptr[rdi + 64], ymm2
VMOVDQA	ymmword ptr[rdi + 96], ymm3
VMOVDQA	ymmword ptr[rdi + 128], ymm4
VMOVDQA	ymmword ptr[rdi + 160], ymm5
VMOVDQA	ymmword ptr[rdi + 192], ymm6
VMOVDQA	ymmword ptr[rdi + 224], ymm7
lea	rdi, [rdi + 256]
lea	r9, [r9 + 256]
 endm

rept	N16_ mod 8

VMOVDQA	ymm0, ymmword ptr[rdi]
vlddqu		ymm8, ymmword ptr [r9]
VPSUBW		ymm0, ymm0, ymm8
VPCMPGTW	ymm8, ymm12, ymm0
VPAND	ymm8, ymm8, ymm13
VPADDW	ymm0, ymm0, ymm8
VMOVDQA	ymmword ptr[rdi], ymm0
lea	rdi, [rdi + 32]
lea	r9, [r9 + 32]

endm

 lea	rsi, [rsi + 2]
 dec	cx;
 jnz	for_plus_label
;endif

; module
endif
;__m256i *pLast1 = (__m256i *)(thread_rh + N_), *res256 = (__m256i *) thread_res/*, *rh256 = (__m256i *)rh*/;

;__m256i *pLast2 = (__m256i *)(thread_rh + N_ - 1);
mov	 rdi, [r14].THREAD_PARAM_STRUCI16_ASM.res
mov		rsi, r12
COMMENT @
lea		rbx, [rsi + N_ * 2];		pLast1
lea		rdx, [rsi + N_ * 2 - 2];	pLast2
; r0 = _mm256_lddqu_si256(pLast1);
vlddqu	ymm0, ymmword ptr [rbx]
;r1 = _mm256_alignr_epi8(r0,
	;	_mm256_permute2x128_si256(r0, r0, _MM_SHUFFLE(0, 0, 2, 0)), 14);
VPERM2I128	ymm1, ymm0, ymm0, 8;
VPALIGNR	ymm1, ymm0, ymm1, 14;	tmp256_1
;r0 = _mm256_add_epi16(rh256[0], r0);
VPADDW	YMM0, YMM0, ymmword ptr [rsi]
;	r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM9, YMM0, YMM13
VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8
;	r0 = _mm256_add_epi16(r0, r1);
VPADDW		YMM0, YMM0, YMM1
; res256[0] = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM9, YMM0, YMM13
VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8
VMOVDQA		ymmword ptr[rdi], ymm0
mov			rax, 32


rept		(N16_ - 1) / 8


	
;r0 = _mm256_add_epi16(_mm256_lddqu_si256(pLast1 + k), rh256[k]);
		vlddqu	YMM0, ymmword ptr[rbx + rax]
		vlddqu	YMM1, ymmword ptr[rbx + rax + 32]
		vlddqu	YMM2, ymmword ptr[rbx + rax + 64]
		vlddqu	YMM3, ymmword ptr[rbx + rax + 96]
		vlddqu	YMM4, ymmword ptr[rbx + rax + 128]
		vlddqu	YMM5, ymmword ptr[rbx + rax + 160]
		vlddqu	YMM6, ymmword ptr[rbx + rax + 192]
		vlddqu	YMM7, ymmword ptr[rbx + rax + 224]
		VPADDW	YMM0, YMM0, ymmword ptr[rsi + rax]
		VPADDW	YMM1, YMM1, ymmword ptr[rsi + rax + 32]
		VPADDW	YMM2, YMM2, ymmword ptr[rsi + rax + 64]
		VPADDW	YMM3, YMM3, ymmword ptr[rsi + rax + 96]
		VPADDW	YMM4, YMM4, ymmword ptr[rsi + rax + 128]
		VPADDW	YMM5, YMM5, ymmword ptr[rsi + rax + 160]
		VPADDW	YMM6, YMM6, ymmword ptr[rsi + rax + 192]
		VPADDW	YMM7, YMM7, ymmword ptr[rsi + rax + 224]
;if 3 * Q_ gt 32767			
;r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
		
		VPCMPEQW	YMM8, YMM0, YMM13
		VPCMPGTW	YMM9, YMM0, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM0, YMM0, YMM8
		
		VPCMPEQW	YMM8, YMM1, YMM13
		VPCMPGTW	YMM9, YMM1, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM1, YMM1, YMM8
		
		VPCMPEQW	YMM8, YMM2, YMM13
		VPCMPGTW	YMM9, YMM2, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM2, YMM2, YMM8

		VPCMPEQW	YMM8, YMM3, YMM13
		VPCMPGTW	YMM9, YMM3, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM3, YMM3, YMM8

		VPCMPEQW	YMM8, YMM4, YMM13
		VPCMPGTW	YMM9, YMM4, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM4, YMM4, YMM8

		VPCMPEQW	YMM8, YMM5, YMM13
		VPCMPGTW	YMM9, YMM5, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM5, YMM5, YMM8

		VPCMPEQW	YMM8, YMM6, YMM13
		VPCMPGTW	YMM9, YMM6, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM6, YMM6, YMM8

		VPCMPEQW	YMM8, YMM7, YMM13
		VPCMPGTW	YMM9, YMM7, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM7, YMM7, YMM8
;endif

		;r0 = _mm256_add_epi16(r0, _mm256_lddqu_si256(pLast2 + k));
		vlddqu	YMM8, ymmword ptr[rdx + rax]
		vlddqu	YMM9, ymmword ptr[rdx  + rax + 32]
		vlddqu	YMM10, ymmword ptr[rdx + rax + 64]
		vlddqu	YMM11, ymmword ptr[rdx + rax + 96]

		VPADDW	YMM0, YMM0, YMM8
		VPADDW	YMM1, YMM1, YMM9
		VPADDW	YMM2, YMM2, YMM10
		VPADDW	YMM3, YMM3, YMM11
		; _mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
		VPCMPEQW	YMM8, YMM0, YMM13
		VPCMPGTW	YMM9, YMM0, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM0, YMM0, YMM8

		VPCMPEQW	YMM8, YMM1, YMM13
		VPCMPGTW	YMM9, YMM1, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM1, YMM1, YMM8

		VPCMPEQW	YMM8, YMM2, YMM13
		VPCMPGTW	YMM9, YMM2, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM2, YMM2, YMM8

		VPCMPEQW	YMM8, YMM3, YMM13
		VPCMPGTW	YMM9, YMM3, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM3, YMM3, YMM8


		vlddqu	YMM8, ymmword ptr[rdx + rax + 128]
		vlddqu	YMM9, ymmword ptr[rdx  + rax + 160]
		vlddqu	YMM10, ymmword ptr[rdx + rax + 192]
		vlddqu	YMM11, ymmword ptr[rdx + rax + 224]

		VPADDW	YMM4, YMM4, YMM8
		VPADDW	YMM5, YMM5, YMM9
		VPADDW	YMM6, YMM6, YMM10
		VPADDW	YMM7, YMM7, YMM11
		; _mm256_store_si256(res256 + k, _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13)))));
		VPCMPEQW	YMM8, YMM4, YMM13
		VPCMPGTW	YMM9, YMM4, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM4, YMM4, YMM8

		VPCMPEQW	YMM8, YMM5, YMM13
		VPCMPGTW	YMM9, YMM5, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM5, YMM5, YMM8

		VPCMPEQW	YMM8, YMM6, YMM13
		VPCMPGTW	YMM9, YMM6, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM6, YMM6, YMM8

		VPCMPEQW	YMM8, YMM7, YMM13
		VPCMPGTW	YMM9, YMM7, YMM13		
		VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM7, YMM7, YMM8

		VMOVDQA		YMMWORD PTR [rdi + rax], YMM0
		VMOVDQA		YMMWORD PTR [rdi + rax + 32], YMM1
		VMOVDQA		YMMWORD PTR [rdi + rax + 64], YMM2
		VMOVDQA		YMMWORD PTR [rdi + rax + 96], YMM3
		VMOVDQA		YMMWORD PTR [rdi + rax + 128], YMM4
		VMOVDQA		YMMWORD PTR [rdi + rax + 160], YMM5
		VMOVDQA		YMMWORD PTR [rdi + rax + 192], YMM6
		VMOVDQA		YMMWORD PTR [rdi + rax + 224], YMM7

		LEA	RAX, [RAX + 256]

endm


rept	(N16_ - 1) mod 8

vlddqu	YMM0, ymmword ptr[rbx + rax]
VPADDW	YMM0, YMM0, ymmword ptr[rsi + rax]

VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM9, YMM0, YMM13		
VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8

vlddqu		YMM8, ymmword ptr[rdx + rax]
VPADDW		YMM0, YMM0, YMM8
VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM9, YMM0, YMM13	
VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8
VMOVDQA		YMMWORD PTR [rdi + rax], YMM0
LEA	RAX, [RAX + 32]

endm



LEA	RAX, [RAX - 32]
VMOVDQA		YMM0,  YMMWORD PTR [rdi + rax]
VPAND		YMM0, YMM0,  YMMWORD PTR [maska256_16]
VMOVDQA		YMMWORD PTR [rdi + rax], YMM0
@
modp_plus rsi, rdi








pop	r15
pop	r14
pop	r13
pop	r12
pop	rdi
pop	rsi
pop	rbx

;movaps      xmm8, xmmword ptr [R11 + 90H];	xmm8
;movaps      xmm7, xmmword ptr [R11 + 80H];	xmm7
;movaps      xmm6, xmmword ptr [R11 + 70H];	xmm6

movaps      xmm9, xmmword ptr [R11 + 40H];	xmm9
movaps      xmm8, xmmword ptr [R11 + 30H];	xmm8
movaps      xmm7, xmmword ptr [R11 + 20H];	xmm7
movaps      xmm6, xmmword ptr [R11 + 10H];	xmm6
movaps      xmm5, xmmword ptr [R11 ];	xmm5

add	rsp, rbp
pop		rbp


ret


thread_mul_asm endp	
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

F_h_mul_asm	proc
push rbp
mov		rbp, rsp
and		rbp, 31

add		rbp, 64 + 16 * 16 +  (N16 * 3 +   AVX_LEN * 9) * 2
sub		rsp, rbp

mov	r11, rsp
add	r11, 64

;  save sse registers

movaps      xmmword ptr [R11 + 00H],xmm5
movaps      xmmword ptr [R11 + 10H],xmm6
movaps      xmmword ptr [R11 + 20H],xmm7
movaps      xmmword ptr [R11 + 30H],xmm8
movaps      xmmword ptr [R11 + 40H],xmm9

; save registers RBX, RBP, RDI, RSI, RSP, R12, R13, R14, and R15.
push	rbx
push	rsi
push	rdi
push	r11
push	r12
push	r13
push	r14
push	r15

; rcx, rdx, r8, r9
; key, h, result

mov		r13, rcx;	key
lea		r12, [r11 + 256 + 32] ; Local area address 
mov		r10, rdx; h
VPXOR	ymm12, ymm12, ymm12; 0
VMOVDQA	ymm13, ymmword ptr [q256_16]; Q

lea		r15, [r12 + (N16 * 3 + AVX_LEN/2) * 2]; predcalch
predcalc r10, r15


; zero array
sub	rax, rax
sub	rbx, rbx
sub	rcx, rcx
sub	rdx, rdx

mov		rdi, r12
mov	ecx, N16 
rep	stosd
;lea	rsi, [r13 + 8 * 2]; minus_reg
mov	rsi, [R13].THREAD_PARAM_STRUCI16_ASM.minus
mov		r14, r12
; r10 - h reg
; r15 - predcalc reg
; r14 - for internal result
;for_minus macro 	count, minus_reg, result_reg, h_reg, predcalc_reg, for_label

mov	cx, [R13].THREAD_PARAM_STRUCI16_ASM.minus_count
for_minus ecx, rsi, r14, r10, r15, for_minus_
lea	rdi, [r12 + N16 * 4]
lea	r15,  [rdi + N16 * 2 + AVX_LEN]
mov	r9, rdi 
h_to_h_	r10, r9
mov		r10, rdi
predcalc r10, r15
mov	rsi, [R13].THREAD_PARAM_STRUCI16_ASM.plus
mov	cx, [R13].THREAD_PARAM_STRUCI16_ASM.plus_count
for_plus ecx, rsi, r14, r10, r15, for_plus_
mov	r8, [R13].THREAD_PARAM_STRUCI16_ASM.res

modp_plus r14, r8

pop	r15
pop	r14
pop	r13
pop	r12
pop	r11
pop	rdi
pop	rsi
pop	rbx


movaps      xmm9, xmmword ptr [R11 + 40H];	xmm9
movaps      xmm8, xmmword ptr [R11 + 30H];	xmm8
movaps      xmm7, xmmword ptr [R11 + 20H];	xmm7
movaps      xmm6, xmmword ptr [R11 + 10H];	xmm6
movaps      xmm5, xmmword ptr [R11 ];	xmm5

add	rsp, rbp
pop		rbp


ret
F_h_mul_asm	endp

 _TEXT ends
end

