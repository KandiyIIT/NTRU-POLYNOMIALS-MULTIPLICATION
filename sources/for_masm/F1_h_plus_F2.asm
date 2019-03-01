include macroses.inc
if 0
INTERNAL_STRUCI16_ASM STRUCT
	internal_res	dw	(AVX_LEN/2 + N16 * 2 )			dup (?)
	h				dw	(N16 + AVX_LEN/2)				dup (?)
	predcalc		dw	(AVX_LEN/2 * 16 )				dup (?); 512
	
	;predcalc_		dw	(AVX_LEN/2 * 16 )				dup (?)
	

INTERNAL_STRUCI16_ASM	ends
endif



if F1F2F3 eq 1

_TEXT    SEGMENT
F1_h_plus_F2_asm	PROC
push rbp
mov		rbp, rsp
and		rbp, 31
; predcalc_ h_ 
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

mov	r13, rcx;	key
lea		r12, [r11 + 256 + 32] ; Local area address 
mov		r10, rdx; h
VPXOR		ymm12, ymm12, ymm12; 0
VMOVDQA		ymm13, ymmword ptr [q256_16]; Q
;mov		rsi, r13;
;mov		rdi, r12
;h_to_h_	rsi, rdi
;mov		rsi, rdx;
lea		r15, [r12 + (N16 * 3 + AVX_LEN/2) * 2]; predcalch
predcalc r10, r15


; zero array
sub	rax, rax
sub	rbx, rbx
sub	rcx, rcx
sub	rdx, rdx

;lea	rdi, [r12 + 32]
mov		rdi, r12
mov	ecx, N16 
rep	stosd
lea	rsi, [r13 + D1_ * 2]; minus_reg
;lea	r14, [r12 + 32]; result_reg
mov		r14, r12
; r10 - h reg
; r15 - predcalc reg
; r14 - for internal result
;for_minus macro 	count, minus_reg, result_reg, h_reg, predcalc_reg, for_label

for_minus D1_, rsi, r14, r10, r15, for_minus_1
;for_minus_without_for D1_, rsi, r14, r10, r15

lea	rdi, [r12 + N16 * 4]
lea	r15,  [rdi + N16 * 2 + AVX_LEN]
mov	r9, rdi 
h_to_h_	r10, r9
mov		r10, rdi
predcalc r10, r15
lea	rsi, [r13 ]; plus_reg

for_plus D1_, rsi, r14, r10, r15, for_plus_1
;for_plus_without_for D1_, rsi, r14, r10, r15

;mov	rsi, r14
;mov	rdi, r8
modp_plus r14, r10
sub		rax, rax
sub		rbx, rbx
sub		rdx, rdx

mov		rdi, r12
mov	ecx, N16 
rep	stosd

predcalc r10, r15

lea	rsi, [r13 + D1_ * 4 + D2_ * 2] ; minus_reg
for_minus D2_, rsi, r14, r10, r15, for_minus_2
;for_minus_without_for D2_, rsi, r14, r10, r15
lea	rdi, [r12 + N16 * 4]
lea	r15,  [rdi + N16 * 2 + AVX_LEN]
mov	r9, rdi 
h_to_h_	r10, r9
mov		r10, rdi
predcalc r10, r15
lea	rsi, [r13 + D1_ * 4 ] ; plus_reg
for_plus D2_, rsi, r14, r10, r15, for_plus_2
;for_plus_without_for D2_, rsi, r14, r10, r15
modp_plus r14, r8

pop	r15
pop	r14
pop	r13
pop	r12
pop r11
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


F1_h_plus_F2_asm endp	
 _TEXT ends
 endif

end
