
%include 'macroses.inc'

global F_h_mul_asm
default rel

SEGMENT .text


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;void F_h_mul_asm (&params[thread], h);
F_h_mul_asm:
push rbp
mov		rbp, rsp
and		rbp, 31

add		rbp, 64 + 16 * 16 +  (N16 * 3 +   AVX_LEN * 9) * 2
sub		rsp, rbp

mov	r11, rsp
add	r11, 64

;  save sse registers

movaps      oword  [R11 + 00H],xmm5
movaps      oword  [R11 + 10H],xmm6
movaps      oword  [R11 + 20H],xmm7
movaps      oword  [R11 + 30H],xmm8
movaps      oword  [R11 + 40H],xmm9

; save registers RBX, RBP, RDI, RSI, RSP, R12, R13, R14, and R15.
push    rdx
push    rcx
push	rbx
;push	rsi
;push	rdi
push	r12
push	r13
push	r14
push	r15


; rcx, rdx, r8, r9
; key, h, result

mov		r13, rdi;	key
lea		r12, [r11 + 256 + 32] ; Local area address 
mov		r10, rsi; h
VPXOR	ymm12, ymm12, ymm12; 0
VMOVDQA	ymm13, yword  [q256_16]; Q

lea		r15, [r12 + (N16 * 3 + AVX_LEN/2) * 2]; predcalch

;predcalc r10, r15
	VMOVDQA	ymm0, yword   [r10]
	VPERM2I128	ymm1, ymm0, ymm0, 8;
	VPALIGNR	ymm1, ymm0, ymm1, 14;
	VPERM2I128	ymm2, ymm1, ymm1, 8;
	VPALIGNR	ymm2, ymm1, ymm2, 14;
	VPERM2I128	ymm3, ymm2, ymm2, 8;
	VPALIGNR	ymm3, ymm2, ymm3, 14;
	VPERM2I128	ymm4, ymm3, ymm3, 8;
	VPALIGNR	ymm4, ymm3, ymm4, 14;
	VPERM2I128	ymm5, ymm4, ymm4, 8;
	VPALIGNR	ymm5, ymm4, ymm5, 14;
	VPERM2I128	ymm6, ymm5, ymm5, 8;
	VPALIGNR	ymm6, ymm5, ymm6, 14;
	VPERM2I128	ymm7, ymm6, ymm6, 8;
	VPALIGNR	ymm7, ymm6, ymm7, 14;
	VMOVDQA	yword   [r15], ymm0
	VMOVDQA	yword   [r15 + 32], ymm1
	VMOVDQA	yword   [r15 + 64], ymm2
	VMOVDQA	yword   [r15 + 96], ymm3
	VMOVDQA	yword   [r15 + 128], ymm4
	VMOVDQA	yword   [r15 + 160], ymm5
	VMOVDQA	yword   [r15 + 192], ymm6
	VMOVDQA	yword   [r15 + 224], ymm7

		
	VPERM2I128	ymm0, ymm7, ymm7, 8;
	VPALIGNR	ymm0, ymm7, ymm0, 14;
	VPERM2I128	ymm1, ymm0, ymm0, 8;
	VPALIGNR	ymm1, ymm0, ymm1, 14;
	VPERM2I128	ymm2, ymm1, ymm1, 8;
	VPALIGNR	ymm2, ymm1, ymm2, 14;
	VPERM2I128	ymm3, ymm2, ymm2, 8;
	VPALIGNR	ymm3, ymm2, ymm3, 14;
	VPERM2I128	ymm4, ymm3, ymm3, 8;
	VPALIGNR	ymm4, ymm3, ymm4, 14;
	VPERM2I128	ymm5, ymm4, ymm4, 8;
	VPALIGNR	ymm5, ymm4, ymm5, 14;
	VPERM2I128	ymm6, ymm5, ymm5, 8;
	VPALIGNR	ymm6, ymm5, ymm6, 14;
	VPERM2I128	ymm7, ymm6, ymm6, 8;
	VPALIGNR	ymm7, ymm6, ymm7, 14;
	VMOVDQA	yword   [r15 + 256], ymm0
	VMOVDQA	yword   [r15 + 288], ymm1
	VMOVDQA	yword   [r15 + 320], ymm2
	VMOVDQA	yword   [r15 + 352], ymm3
	VMOVDQA	yword   [r15 + 384], ymm4
	VMOVDQA	yword   [r15 + 416], ymm5
	VMOVDQA	yword   [r15 + 448], ymm6
	VMOVDQA	yword   [r15 + 480], ymm7
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;mov r8,[r13+THREAD_PARAM_STRUCI16_ASM.res]
;mov ecx,512/4
;temp_m1:
;mov eax,[r15]
;mov [r8],eax
;add r15,4
;add r8,4
;dec ecx
;jnz temp_m1

;%if 0
; zero array
sub	rax, rax
sub	rbx, rbx
sub	rcx, rcx
sub	rdx, rdx
 
mov		rdi, r12
mov	ecx, N16 
rep	stosd
;lea	rsi, [r13 + 8 * 2]; minus_reg
mov	rsi, [R13+THREAD_PARAM_STRUCI16_ASM.minus]
mov		r14, r12
; r10 - h reg
; r15 - predcalc reg
; r14 - for internal result
;for_minus macro 	count, minus_reg, result_reg, h_reg, predcalc_reg, for_label

mov	cx, [R13+THREAD_PARAM_STRUCI16_ASM.minus_count]
for_minus ecx, rsi, r14, r10, r15, for_minus_
lea	rdi, [r12 + N16 * 4]
lea	r15,  [rdi + N16 * 2 + AVX_LEN]
mov	r9, rdi 
h_to_h_	r10, r9
temp_m2:
mov		r10, rdi
predcalc r10, r15
mov	rsi, [R13+THREAD_PARAM_STRUCI16_ASM.plus]
mov	cx, [R13+THREAD_PARAM_STRUCI16_ASM.plus_count]
for_plus ecx, rsi, r14, r10, r15, for_plus_
mov	r8, [R13+THREAD_PARAM_STRUCI16_ASM.res]

modp_plus r14, r8
;%endif
pop	r15
pop	r14
pop	r13
pop	r12
;pop	rdi
;pop	rsi
pop rbx
pop rcx
pop rdx


movaps      xmm9, oword  [R11 + 40H];	xmm9
movaps      xmm8, oword  [R11 + 30H];	xmm8
movaps      xmm7, oword  [R11 + 20H];	xmm7
movaps      xmm6, oword  [R11 + 10H];	xmm6
movaps      xmm5, oword  [R11 ];	xmm5

add	rsp, rbp
pop		rbp


ret
;F_h_mul_asm	endp

; _TEXT ends


