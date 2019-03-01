include parameters.inc
; rsi - src pointer
;rdi	dest pointer
modp_plus	MACRO	 src_reg, dest_reg 
lea		rbx, [src_reg + N_ * 2];		pLast1
lea		rdx, [src_reg + N_ * 2 - 2];	pLast2
; r0 = _mm256_lddqu_si256(pLast1);
vlddqu	ymm0, ymmword ptr [rbx]
VPERM2I128	ymm1, ymm0, ymm0, 8;
VPALIGNR	ymm1, ymm0, ymm1, 14;	tmp256_1
;r0 = _mm256_add_epi16(rh256[0], r0);
VPADDW	YMM0, YMM0, ymmword ptr [src_reg]
;	r0 = _mm256_sub_epi16(r0, _mm256_and_si256(r13, _mm256_xor_si256(_mm256_cmpgt_epi16(r0, r13), _mm256_cmpeq_epi16(r0, r13))));
;VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM8, YMM0, YMM13
;VPXOR		YMM8, YMM8, YMM9
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
VMOVDQA		ymmword ptr[dest_reg], ymm0
mov			rax, 32

rept		(N16_ - 1) / 8
		vlddqu	YMM0, ymmword ptr[rbx + rax]
		vlddqu	YMM1, ymmword ptr[rbx + rax + 32]
		vlddqu	YMM2, ymmword ptr[rbx + rax + 64]
		vlddqu	YMM3, ymmword ptr[rbx + rax + 96]
		vlddqu	YMM4, ymmword ptr[rbx + rax + 128]
		vlddqu	YMM5, ymmword ptr[rbx + rax + 160]
		vlddqu	YMM6, ymmword ptr[rbx + rax + 192]
		vlddqu	YMM7, ymmword ptr[rbx + rax + 224]
		VPADDW	YMM0, YMM0, ymmword ptr[src_reg + rax]
		VPADDW	YMM1, YMM1, ymmword ptr[src_reg + rax + 32]
		VPADDW	YMM2, YMM2, ymmword ptr[src_reg + rax + 64]
		VPADDW	YMM3, YMM3, ymmword ptr[src_reg + rax + 96]
		VPADDW	YMM4, YMM4, ymmword ptr[src_reg + rax + 128]
		VPADDW	YMM5, YMM5, ymmword ptr[src_reg + rax + 160]
		VPADDW	YMM6, YMM6, ymmword ptr[src_reg + rax + 192]
		VPADDW	YMM7, YMM7, ymmword ptr[src_reg + rax + 224]
		
		;VPCMPEQW	YMM8, YMM0, YMM13
		VPCMPGTW	YMM8, YMM0, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM0, YMM0, YMM8
		
		;VPCMPEQW	YMM8, YMM1, YMM13
		VPCMPGTW	YMM8, YMM1, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM1, YMM1, YMM8
		
		;VPCMPEQW	YMM8, YMM2, YMM13
		VPCMPGTW	YMM8, YMM2, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM2, YMM2, YMM8

		;VPCMPEQW	YMM8, YMM3, YMM13
		VPCMPGTW	YMM8, YMM3, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM3, YMM3, YMM8

		;VPCMPEQW	YMM8, YMM4, YMM13
		VPCMPGTW	YMM8, YMM4, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM4, YMM4, YMM8

		;VPCMPEQW	YMM8, YMM5, YMM13
		VPCMPGTW	YMM8, YMM5, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM5, YMM5, YMM8

		;VPCMPEQW	YMM8, YMM6, YMM13
		VPCMPGTW	YMM8, YMM6, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM6, YMM6, YMM8

		;VPCMPEQW	YMM8, YMM7, YMM13
		VPCMPGTW	YMM8, YMM7, YMM13		
		;VPXOR		YMM8, YMM8, YMM9
		VPAND		YMM8, YMM8, YMM13
		VPSUBW		YMM7, YMM7, YMM8


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

		VMOVDQA		YMMWORD PTR [dest_reg + rax], YMM0
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 32], YMM1
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 64], YMM2
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 96], YMM3
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 128], YMM4
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 160], YMM5
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 192], YMM6
		VMOVDQA		YMMWORD PTR [dest_reg + rax + 224], YMM7

		LEA	RAX, [RAX + 256]

endm

rept	(N16_ - 1) mod 8

vlddqu	YMM0, ymmword ptr[rbx + rax]
VPADDW	YMM0, YMM0, ymmword ptr[src_reg + rax]

;VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM8, YMM0, YMM13		
;VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8

vlddqu		YMM8, ymmword ptr[rdx + rax]
VPADDW		YMM0, YMM0, YMM8
VPCMPEQW	YMM8, YMM0, YMM13
VPCMPGTW	YMM9, YMM0, YMM13	
VPXOR		YMM8, YMM8, YMM9
VPAND		YMM8, YMM8, YMM13
VPSUBW		YMM0, YMM0, YMM8
VMOVDQA		YMMWORD PTR [dest_reg + rax], YMM0
LEA	RAX, [RAX + 32]

endm

LEA	RAX, [RAX - 32]
VMOVDQA		YMM0,  YMMWORD PTR [dest_reg + rax]
VPAND		YMM0, YMM0,  YMMWORD PTR [maska256_16]
VMOVDQA		YMMWORD PTR [dest_reg + rax], YMM0

endm
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; h to h_
h_to_h_  macro	srcreg, destreg

rept (N16_ + 1)/8
	VMOVDQA	YMM0,  YMMWORD PTR [srcreg]
	VMOVDQA	YMM1,  YMMWORD PTR [srcreg + 32]
	VMOVDQA	YMM2,  YMMWORD PTR [srcreg + 64]
	VMOVDQA	YMM3,  YMMWORD PTR [srcreg + 96]
	VMOVDQA	YMM4,  YMMWORD PTR [srcreg + 128]
	VMOVDQA	YMM5,  YMMWORD PTR [srcreg + 160]
	VMOVDQA	YMM6,  YMMWORD PTR [srcreg + 192]
	VMOVDQA	YMM7,  YMMWORD PTR [srcreg + 224]
	
	VPCMPEQW	YMM8, YMM0, YMM12
	
	VPCMPEQW	YMM9, YMM1, YMM12
	VPCMPEQW	YMM10, YMM2, YMM12
	VPCMPEQW	YMM11, YMM3, YMM12
	
	
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13
			
	VPSUBW		YMM0, YMM8, YMM0
	VPSUBW		YMM1, YMM9, YMM1
	VPSUBW		YMM2, YMM10, YMM2
	VPSUBW		YMM3, YMM11, YMM3
	

	VPCMPEQW	YMM8, YMM4, YMM12
	VPCMPEQW	YMM9, YMM5, YMM12
	VPCMPEQW	YMM10, YMM6, YMM12
	VPCMPEQW	YMM11, YMM7, YMM12

	
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13

	

	VPSUBW		YMM4, YMM8, YMM4
	VPSUBW		YMM5, YMM9, YMM5
	VPSUBW		YMM6, YMM10, YMM6
	VPSUBW		YMM7, YMM11, YMM7
	
	
	VMOVDQA	YMMWORD PTR [destreg],		YMM0
	VMOVDQA	YMMWORD PTR [destreg + 32], YMM1
	VMOVDQA	YMMWORD PTR [destreg + 64], YMM2
	VMOVDQA	YMMWORD PTR [destreg + 96], YMM3
	VMOVDQA	YMMWORD PTR [destreg + 128],YMM4
	VMOVDQA	YMMWORD PTR [destreg + 160], YMM5
	VMOVDQA	YMMWORD PTR [destreg + 192], YMM6
	VMOVDQA	YMMWORD PTR [destreg + 224], YMM7
	
	lea	destreg, [destreg + 256]
	lea	srcreg, [srcreg + 256]
	

	endm
	
	rept (N16_ + 1) mod 8
		VMOVDQA	YMM0,  YMMWORD PTR [srcreg]
		VPCMPEQW	YMM8, YMM0, YMM12
		VPANDN	YMM8, YMM8, YMM13
		VPSUBW		YMM0, YMM8, YMM0
		VMOVDQA	YMMWORD PTR [destreg], YMM0
		
		lea	destreg, [destreg + 32]
		lea	srcreg, [srcreg + 32]
		

	endm

endm

predcalc12  macro	srcreg, destreg, destreg1 
	;dest[0] = src[0];	\
	VMOVDQA	ymm0, YMMWORD PTR [srcreg]
	;_mm256_permute2x128_si256(dest[0], dest[0], _MM_SHUFFLE(0, 0, 2, 0)), 14);	\
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
	VMOVDQA	YMMWORD PTR [destreg], ymm0
	VMOVDQA	YMMWORD PTR [destreg + 32], ymm1
	VMOVDQA	YMMWORD PTR [destreg + 64], ymm2
	VMOVDQA	YMMWORD PTR [destreg + 96], ymm3
	VMOVDQA	YMMWORD PTR [destreg + 128], ymm4
	VMOVDQA	YMMWORD PTR [destreg + 160], ymm5
	VMOVDQA	YMMWORD PTR [destreg + 192], ymm6
	VMOVDQA	YMMWORD PTR [destreg + 224], ymm7

	VPCMPEQW	YMM8, YMM0, YMM12
	VPCMPEQW	YMM9, YMM1, YMM12
	VPCMPEQW	YMM10, YMM2, YMM12
	VPCMPEQW	YMM11, YMM3, YMM12
		
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13
			
	VPSUBW		YMM0, YMM8, YMM0
	VPSUBW		YMM1, YMM9, YMM1
	VPSUBW		YMM2, YMM10, YMM2
	VPSUBW		YMM3, YMM11, YMM3

	VPCMPEQW	YMM8, YMM4, YMM12
	VPCMPEQW	YMM9, YMM5, YMM12
	VPCMPEQW	YMM10, YMM6, YMM12
	VPCMPEQW	YMM11, YMM7, YMM12

	
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13
	

	VPSUBW		YMM4, YMM8, YMM4
	VPSUBW		YMM5, YMM9, YMM5
	VPSUBW		YMM6, YMM10, YMM6
	VPSUBW		YMM8, YMM11, YMM7

	VMOVDQA	YMMWORD PTR [destreg1], ymm0
	VMOVDQA	YMMWORD PTR [destreg1 + 32], ymm1
	VMOVDQA	YMMWORD PTR [destreg1 + 64], ymm2
	VMOVDQA	YMMWORD PTR [destreg1 + 96], ymm3
	VMOVDQA	YMMWORD PTR [destreg1 + 128], ymm4
	VMOVDQA	YMMWORD PTR [destreg1 + 160], ymm5
	VMOVDQA	YMMWORD PTR [destreg1 + 192], ymm6
	VMOVDQA	YMMWORD PTR [destreg1 + 224], ymm8
	
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
	VMOVDQA	YMMWORD PTR [destreg + 256], ymm0
	VMOVDQA	YMMWORD PTR [destreg + 288], ymm1
	VMOVDQA	YMMWORD PTR [destreg + 320], ymm2
	VMOVDQA	YMMWORD PTR [destreg + 352], ymm3
	VMOVDQA	YMMWORD PTR [destreg + 384], ymm4
	VMOVDQA	YMMWORD PTR [destreg + 416], ymm5
	VMOVDQA	YMMWORD PTR [destreg + 448], ymm6
	VMOVDQA	YMMWORD PTR [destreg + 480], ymm7

	VPCMPEQW	YMM8, YMM0, YMM12
	VPCMPEQW	YMM9, YMM1, YMM12
	VPCMPEQW	YMM10, YMM2, YMM12
	VPCMPEQW	YMM11, YMM3, YMM12
		
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13
			
	VPSUBW		YMM0, YMM8, YMM0
	VPSUBW		YMM1, YMM9, YMM1
	VPSUBW		YMM2, YMM10, YMM2
	VPSUBW		YMM3, YMM11, YMM3

	VPCMPEQW	YMM8, YMM4, YMM12
	VPCMPEQW	YMM9, YMM5, YMM12
	VPCMPEQW	YMM10, YMM6, YMM12
	VPCMPEQW	YMM11, YMM7, YMM12

	
	VPANDN	YMM8, YMM8, YMM13
	VPANDN	YMM9, YMM9, YMM13
	VPANDN	YMM10, YMM10, YMM13
	VPANDN	YMM11, YMM11, YMM13
	

	VPSUBW		YMM4, YMM8, YMM4
	VPSUBW		YMM5, YMM9, YMM5
	VPSUBW		YMM6, YMM10, YMM6
	VPSUBW		YMM7, YMM11, YMM7

	VMOVDQA	YMMWORD PTR [destreg1 + 256], ymm0
	VMOVDQA	YMMWORD PTR [destreg1 + 288], ymm1
	VMOVDQA	YMMWORD PTR [destreg1 + 320], ymm2
	VMOVDQA	YMMWORD PTR [destreg1 + 352], ymm3
	VMOVDQA	YMMWORD PTR [destreg1 + 384], ymm4
	VMOVDQA	YMMWORD PTR [destreg1 + 416], ymm5
	VMOVDQA	YMMWORD PTR [destreg1 + 448], ymm6
	VMOVDQA	YMMWORD PTR [destreg1 + 480], ymm7


endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
predcalc  macro	srcreg, destreg 
	;dest[0] = src[0];	\
	VMOVDQA	ymm0, YMMWORD PTR [srcreg]
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
	VMOVDQA	YMMWORD PTR [destreg], ymm0
	VMOVDQA	YMMWORD PTR [destreg + 32], ymm1
	VMOVDQA	YMMWORD PTR [destreg + 64], ymm2
	VMOVDQA	YMMWORD PTR [destreg + 96], ymm3
	VMOVDQA	YMMWORD PTR [destreg + 128], ymm4
	VMOVDQA	YMMWORD PTR [destreg + 160], ymm5
	VMOVDQA	YMMWORD PTR [destreg + 192], ymm6
	VMOVDQA	YMMWORD PTR [destreg + 224], ymm7

		
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
	VMOVDQA	YMMWORD PTR [destreg + 256], ymm0
	VMOVDQA	YMMWORD PTR [destreg + 288], ymm1
	VMOVDQA	YMMWORD PTR [destreg + 320], ymm2
	VMOVDQA	YMMWORD PTR [destreg + 352], ymm3
	VMOVDQA	YMMWORD PTR [destreg + 384], ymm4
	VMOVDQA	YMMWORD PTR [destreg + 416], ymm5
	VMOVDQA	YMMWORD PTR [destreg + 448], ymm6
	VMOVDQA	YMMWORD PTR [destreg + 480], ymm7

endm
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; minus_reg
; result_reg 
; h_reg
;predcalc_reg 
; cx - количество (константа)

for_minus macro 	count, minus_reg, result_reg, h_reg, predcalc_reg, for_label

mov ecx, count 
for_label:
mov	ax, [minus_reg]

;line = k % 16;
mov	bx, ax
and	bx, 15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setz	dl
mov	r11, rdx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov	dx, bx
sub	dx, 16
neg	dx

lea	r9, [h_reg + rdx * 2]; predcalc


shl	bx, 5
;col = k >> 4
mov	dx, ax
shr	dx, 4
shl	dx, 5
; ck256 = rh256 + col;
lea	rdi, [result_reg + rdx]; 
;r0 = _mm256_sub_epi16(ck256[0], thread_coeffs[line]);
VMOVDQA	ymm0, ymmword ptr [rdi]
VPSUBW	ymm0, ymm0, ymmword ptr [predcalc_reg + rbx]

VPCMPGTW	ymm1, ymm12, ymm0

VPAND	ymm1, ymm1, ymm13

VPADDW	ymm0, ymm0, ymm1
VMOVDQA	ymmword ptr [rdi], ymm0

lea	rdi, [rdi + 32];

 REPT N16_ / 8
 
 VMOVDQA	ymm0, ymmword ptr[rdi]
 VMOVDQA	ymm1, ymmword ptr[rdi + 32]
 VMOVDQA	ymm2, ymmword ptr[rdi + 64]
 VMOVDQA	ymm3, ymmword ptr[rdi + 96]
 VMOVDQA	ymm4, ymmword ptr[rdi + 128]
 VMOVDQA	ymm5, ymmword ptr[rdi + 160]
 VMOVDQA	ymm6, ymmword ptr[rdi + 192]
 VMOVDQA	ymm7, ymmword ptr[rdi + 224]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 vlddqu		ymm8, ymmword ptr [rdi + r11 * 2]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 32]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 64]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 96]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 vlddqu		ymm8, ymmword ptr [r9]
 vlddqu		ymm9, ymmword ptr [r9 + 32]
 vlddqu		ymm10, ymmword ptr [r9 + 64]
 vlddqu		ymm11, ymmword ptr [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 vlddqu		ymm8, ymmword ptr [rdi + r11 * 2 + 128]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 160]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 192]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 224]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 vlddqu		ymm8, ymmword ptr [r9 + 128]
 vlddqu		ymm9, ymmword ptr [r9 + 160]
 vlddqu		ymm10, ymmword ptr [r9 + 192]
 vlddqu		ymm11, ymmword ptr [r9 + 224]
 
 VPSUBW		ymm4, ymm4, ymm8
 VPSUBW		ymm5, ymm5, ymm9
 VPSUBW		ymm6, ymm6, ymm10
 VPSUBW		ymm7, ymm7, ymm11
 
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
 dec	ecx;
 jnz	for_label
 
 

endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; minus_reg
; result_reg 
; h_reg
;predcalc_reg 
; cx - количество (константа)

for_minus_without_for macro 	count, minus_reg, result_reg, h_reg, predcalc_reg

;mov ecx, count 
;for_label:
rept count
mov	ax, [minus_reg]
;line = k % 16;
mov	bx, ax
and	bx, 15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setz	dl
mov	r11, rdx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

mov	dx, bx
sub	dx, 16
neg	dx

lea	r9, [h_reg + rdx * 2]; predcalc
shl	bx, 5
;col = k >> 4
mov	dx, ax
shr	dx, 4
shl	dx, 5
; ck256 = rh256 + col;
lea	rdi, [result_reg + rdx]; 
;r0 = _mm256_sub_epi16(ck256[0], thread_coeffs[line]);
VMOVDQA	ymm0, ymmword ptr [rdi]
VPSUBW	ymm0, ymm0, ymmword ptr [predcalc_reg + rbx]

VPCMPGTW	ymm1, ymm12, ymm0

VPAND	ymm1, ymm1, ymm13

VPADDW	ymm0, ymm0, ymm1
VMOVDQA	ymmword ptr [rdi], ymm0

lea	rdi, [rdi + 32];

 REPT N16_ / 8
 
 VMOVDQA	ymm0, ymmword ptr[rdi]
 VMOVDQA	ymm1, ymmword ptr[rdi + 32]
 VMOVDQA	ymm2, ymmword ptr[rdi + 64]
 VMOVDQA	ymm3, ymmword ptr[rdi + 96]
 VMOVDQA	ymm4, ymmword ptr[rdi + 128]
 VMOVDQA	ymm5, ymmword ptr[rdi + 160]
 VMOVDQA	ymm6, ymmword ptr[rdi + 192]
 VMOVDQA	ymm7, ymmword ptr[rdi + 224]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 vlddqu		ymm8, ymmword ptr [rdi + r11 * 2]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 32]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 64]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 96]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 
 vlddqu		ymm8, ymmword ptr [r9]
 vlddqu		ymm9, ymmword ptr [r9 + 32]
 vlddqu		ymm10, ymmword ptr [r9 + 64]
 vlddqu		ymm11, ymmword ptr [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 vlddqu		ymm8, ymmword ptr [rdi + r11 * 2 + 128]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 160]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 192]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 224]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 vlddqu		ymm8, ymmword ptr [r9 + 128]
 vlddqu		ymm9, ymmword ptr [r9 + 160]
 vlddqu		ymm10, ymmword ptr [r9 + 192]
 vlddqu		ymm11, ymmword ptr [r9 + 224]
 
 VPSUBW		ymm4, ymm4, ymm8
 VPSUBW		ymm5, ymm5, ymm9
 VPSUBW		ymm6, ymm6, ymm10
 VPSUBW		ymm7, ymm7, ymm11
 
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
; dec	ecx;
; jnz	for_label
endm
 
endm
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
for_plus macro 	count, plus_reg, result_reg, h_reg, predcalc_reg, for_label
mov	rdi, result_reg
mov	ecx, count
; k = thread_pk_minus[i];
;mov	rsi, plus_reg

;mov	r15, predcalc_reg
;mov	r10, h_reg
; for (i = 0; i < thread_nums_plus; i++)
;if 0
for_label:
;k = thread_pk_plus[i];
mov	ax, [rsi]
;		line = k % 16;
mov	bx, ax
and	bx, 15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setz	dl
mov	r11, rdx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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

 VPCMPGTW	ymm8, ymm12, ymm0
 VPAND		ymm8, ymm8, ymm13
 VPADDW		ymm0, ymm0, ymm8
 VMOVDQA	ymmword ptr [rdi], ymm0
 lea		rdi, [rdi + 32]

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
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  vlddqu		ymm8, ymmword ptr [rdi + r11 * 2]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 32]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 64]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 96]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 
 vlddqu		ymm8, ymmword ptr [r9]
 vlddqu		ymm9, ymmword ptr [r9 + 32]
 vlddqu		ymm10, ymmword ptr [r9 + 64]
 vlddqu		ymm11, ymmword ptr [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 vlddqu		ymm8, ymmword ptr [rdi + r11 * 2 + 128]
 vlddqu		ymm9, ymmword ptr [rdi + r11 * 2 + 160]
 vlddqu		ymm10, ymmword ptr [rdi + r11 * 2 + 192]
 vlddqu		ymm11, ymmword ptr [rdi + r11 * 2 + 224]
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
 jnz	for_label
 ;endif

endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
for_plus_without_for macro 	count, plus_reg, result_reg, h_reg, predcalc_reg
mov	rdi, result_reg
;mov	ecx, count
; k = thread_pk_minus[i];
;mov	rsi, plus_reg

;mov	r15, predcalc_reg
;mov	r10, h_reg
; for (i = 0; i < thread_nums_plus; i++)
;if 0
;for_label:
;k = thread_pk_plus[i];
rept count

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

 VPCMPGTW	ymm8, ymm12, ymm0
 VPAND		ymm8, ymm8, ymm13
 VPADDW		ymm0, ymm0, ymm8
 VMOVDQA	ymmword ptr [rdi], ymm0
 lea		rdi, [rdi + 32]

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
 ;dec	cx;
 ;jnz	for_label
 ;endif
 endm

endm