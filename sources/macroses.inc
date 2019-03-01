%include 'parameters.inc'


; rsi - src pointer
;rdi	dest pointer
%macro modp_plus  2 
;src_reg, dest_reg 
    lea		rbx, [%1 + N_ * 2];		pLast1
    lea		rdx, [%1 + N_ * 2 - 2];	pLast2
; r0 = _mm256_lddqu_si256(pLast1);
    vlddqu	ymm0, yword   [rbx]
    VPERM2I128	ymm1, ymm0, ymm0, 8;
    VPALIGNR	ymm1, ymm0, ymm1, 14;	tmp256_1
;r0 = _mm256_add_epi16(rh256[0], r0);
    VPADDW	YMM0, YMM0, yword   [%1]
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
    VMOVDQA		yword  [%2], ymm0
    mov			rax, 32

    %rep		(N16_ - 1) / 8
		vlddqu	YMM0, yword  [rbx + rax]
		vlddqu	YMM1, yword  [rbx + rax + 32]
		vlddqu	YMM2, yword  [rbx + rax + 64]
		vlddqu	YMM3, yword  [rbx + rax + 96]
		vlddqu	YMM4, yword  [rbx + rax + 128]
		vlddqu	YMM5, yword  [rbx + rax + 160]
		vlddqu	YMM6, yword  [rbx + rax + 192]
		vlddqu	YMM7, yword  [rbx + rax + 224]
		VPADDW	YMM0, YMM0, yword  [%1 + rax]
		VPADDW	YMM1, YMM1, yword  [%1 + rax + 32]
		VPADDW	YMM2, YMM2, yword  [%1 + rax + 64]
		VPADDW	YMM3, YMM3, yword  [%1 + rax + 96]
		VPADDW	YMM4, YMM4, yword  [%1 + rax + 128]
		VPADDW	YMM5, YMM5, yword  [%1 + rax + 160]
		VPADDW	YMM6, YMM6, yword  [%1 + rax + 192]
		VPADDW	YMM7, YMM7, yword  [%1 + rax + 224]
		
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
		vlddqu	YMM8, yword  [rdx + rax]
		vlddqu	YMM9, yword  [rdx  + rax + 32]
		vlddqu	YMM10, yword  [rdx + rax + 64]
		vlddqu	YMM11, yword  [rdx + rax + 96]

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


		vlddqu	YMM8, yword  [rdx + rax + 128]
		vlddqu	YMM9, yword  [rdx  + rax + 160]
		vlddqu	YMM10, yword  [rdx + rax + 192]
		vlddqu	YMM11, yword  [rdx + rax + 224]

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

		VMOVDQA		yword   [%2 + rax], YMM0
		VMOVDQA		yword   [%2 + rax + 32], YMM1
		VMOVDQA		yword   [%2 + rax + 64], YMM2
		VMOVDQA		yword   [%2 + rax + 96], YMM3
		VMOVDQA		yword   [%2 + rax + 128], YMM4
		VMOVDQA		yword   [%2 + rax + 160], YMM5
		VMOVDQA		yword   [%2 + rax + 192], YMM6
		VMOVDQA		yword   [%2 + rax + 224], YMM7

		LEA	RAX, [RAX + 256]

    %endrep

    %rep	(N16_ - 1) % 8

        vlddqu	YMM0, yword  [rbx + rax]
        VPADDW	YMM0, YMM0, yword  [%1 + rax]

;VPCMPEQW	YMM8, YMM0, YMM13
        VPCMPGTW	YMM8, YMM0, YMM13		
;VPXOR		YMM8, YMM8, YMM9
        VPAND		YMM8, YMM8, YMM13
        VPSUBW		YMM0, YMM0, YMM8

        vlddqu		YMM8, yword  [rdx + rax]
        VPADDW		YMM0, YMM0, YMM8
        VPCMPEQW	YMM8, YMM0, YMM13
        VPCMPGTW	YMM9, YMM0, YMM13	
        VPXOR		YMM8, YMM8, YMM9
        VPAND		YMM8, YMM8, YMM13
        VPSUBW		YMM0, YMM0, YMM8
        VMOVDQA		yword   [%2 + rax], YMM0
        LEA	RAX, [RAX + 32]

    %endrep

    LEA	RAX, [RAX - 32]
    VMOVDQA		YMM0,  yword   [%2 + rax]
    VPAND		YMM0, YMM0,  yword   [maska256_16]
    VMOVDQA		yword   [%2 + rax], YMM0

%endmacro



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; h to h_
%macro h_to_h_  2
;srcreg, destreg

    %rep (N16_ + 1)/8
        VMOVDQA	YMM0,  yword   [ %1]
        VMOVDQA	YMM1,  yword   [ %1 + 32]
        VMOVDQA	YMM2,  yword   [ %1 + 64]
        VMOVDQA	YMM3,  yword   [ %1 + 96]
        VMOVDQA	YMM4,  yword   [ %1 + 128]
        VMOVDQA	YMM5,  yword   [ %1 + 160]
        VMOVDQA	YMM6,  yword   [ %1 + 192]
        VMOVDQA	YMM7,  yword   [ %1 + 224]
	
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
	
	
        VMOVDQA	yword   [ %2],		YMM0
        VMOVDQA	yword   [ %2 + 32], YMM1
        VMOVDQA	yword   [ %2 + 64], YMM2
        VMOVDQA	yword   [ %2 + 96], YMM3
        VMOVDQA	yword   [ %2 + 128],YMM4
        VMOVDQA	yword   [ %2 + 160], YMM5
        VMOVDQA	yword   [ %2 + 192], YMM6
        VMOVDQA	yword   [ %2 + 224], YMM7
	
        lea	 %2, [ %2 + 256]
        lea	 %1, [ %1 + 256]
	

	%endrep
	
	%rep (N16_ + 1) % 8
		VMOVDQA	YMM0,  yword   [ %1]
		VPCMPEQW	YMM8, YMM0, YMM12
		VPANDN	YMM8, YMM8, YMM13
		VPSUBW		YMM0, YMM8, YMM0
		VMOVDQA	yword   [ %2], YMM0
		
		lea	 %2, [ %2 + 32]
		lea	 %1, [ %1 + 32]
		

	%endrep

%endmacro


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro predcalc12  3
;macro	srcreg, destreg, destreg1 
	;dest[0] = src[0];	\
	VMOVDQA	ymm0, yword   [ %1]
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
	VMOVDQA	yword   [ %2], ymm0
	VMOVDQA	yword   [ %2 + 32], ymm1
	VMOVDQA	yword   [ %2 + 64], ymm2
	VMOVDQA	yword   [ %2 + 96], ymm3
	VMOVDQA	yword   [ %2 + 128], ymm4
	VMOVDQA	yword   [ %2 + 160], ymm5
	VMOVDQA	yword   [ %2 + 192], ymm6
	VMOVDQA	yword   [ %2 + 224], ymm7

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

	VMOVDQA	yword   [ %3], ymm0
	VMOVDQA	yword   [ %3 + 32], ymm1
	VMOVDQA	yword   [ %3 + 64], ymm2
	VMOVDQA	yword   [ %3 + 96], ymm3
	VMOVDQA	yword   [ %3 + 128], ymm4
	VMOVDQA	yword   [ %3 + 160], ymm5
	VMOVDQA	yword   [ %3 + 192], ymm6
	VMOVDQA	yword   [ %3 + 224], ymm8
	
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
	VMOVDQA	yword   [ %2 + 256], ymm0
	VMOVDQA	yword   [ %2 + 288], ymm1
	VMOVDQA	yword   [ %2 + 320], ymm2
	VMOVDQA	yword   [ %2 + 352], ymm3
	VMOVDQA	yword   [ %2 + 384], ymm4
	VMOVDQA	yword   [ %2 + 416], ymm5
	VMOVDQA	yword   [ %2 + 448], ymm6
	VMOVDQA	yword   [ %2 + 480], ymm7

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

	VMOVDQA	yword   [ %3 + 256], ymm0
	VMOVDQA	yword   [ %3 + 288], ymm1
	VMOVDQA	yword   [ %3 + 320], ymm2
	VMOVDQA	yword   [ %3 + 352], ymm3
	VMOVDQA	yword   [ %3 + 384], ymm4
	VMOVDQA	yword   [ %3 + 416], ymm5
	VMOVDQA	yword   [ %3 + 448], ymm6
	VMOVDQA	yword   [ %3 + 480], ymm7


%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro predcalc  2 
;srcreg, destreg 
	;dest[0] = src[0];	
	VMOVDQA	ymm0, yword   [%1]
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
	VMOVDQA	yword   [%2], ymm0
	VMOVDQA	yword   [%2 + 32], ymm1
	VMOVDQA	yword   [%2 + 64], ymm2
	VMOVDQA	yword   [%2 + 96], ymm3
	VMOVDQA	yword   [%2 + 128], ymm4
	VMOVDQA	yword   [%2 + 160], ymm5
	VMOVDQA	yword   [%2 + 192], ymm6
	VMOVDQA	yword   [%2 + 224], ymm7

		
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
	VMOVDQA	yword   [%2 + 256], ymm0
	VMOVDQA	yword   [%2 + 288], ymm1
	VMOVDQA	yword   [%2 + 320], ymm2
	VMOVDQA	yword   [%2 + 352], ymm3
	VMOVDQA	yword   [%2 + 384], ymm4
	VMOVDQA	yword   [%2 + 416], ymm5
	VMOVDQA	yword   [%2 + 448], ymm6
	VMOVDQA	yword   [%2 + 480], ymm7

%endmacro
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; minus_reg
; result_reg 
; h_reg
;predcalc_reg 
; cx - количество (константа)

%macro for_minus 6 	
;count, minus_reg, result_reg, h_reg, predcalc_reg, for_label

mov ecx, %1
%6:
mov	ax, [%2]
;line = k % 16;
mov	bx, ax
and	bx, 15
mov	dx, bx
sub	dx, 16
neg	dx

lea	r9, [%4 + rdx * 2]; predcalc
shl	bx, 5
;col = k >> 4
mov	dx, ax
shr	dx, 4
shl	dx, 5
; ck256 = rh256 + col;
lea	rdi, [%3 + rdx]; 
;r0 = _mm256_sub_epi16(ck256[0], thread_coeffs[line]);
VMOVDQA	ymm0, yword   [rdi]
VPSUBW	ymm0, ymm0, yword   [%5 + rbx]

VPCMPGTW	ymm1, ymm12, ymm0

VPAND	ymm1, ymm1, ymm13

VPADDW	ymm0, ymm0, ymm1
VMOVDQA	yword   [rdi], ymm0

lea	rdi, [rdi + 32];

 %REP N16_ / 8
 
 VMOVDQA	ymm0, yword  [rdi]
 VMOVDQA	ymm1, yword  [rdi + 32]
 VMOVDQA	ymm2, yword  [rdi + 64]
 VMOVDQA	ymm3, yword  [rdi + 96]
 VMOVDQA	ymm4, yword  [rdi + 128]
 VMOVDQA	ymm5, yword  [rdi + 160]
 VMOVDQA	ymm6, yword  [rdi + 192]
 VMOVDQA	ymm7, yword  [rdi + 224]
 
 vlddqu		ymm8, yword   [r9]
 vlddqu		ymm9, yword   [r9 + 32]
 vlddqu		ymm10, yword   [r9 + 64]
 vlddqu		ymm11, yword   [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11

 vlddqu		ymm8, yword   [r9 + 128]
 vlddqu		ymm9, yword   [r9 + 160]
 vlddqu		ymm10, yword   [r9 + 192]
 vlddqu		ymm11, yword   [r9 + 224]
 
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

VMOVDQA	yword  [rdi], ymm0
VMOVDQA	yword  [rdi + 32], ymm1
VMOVDQA	yword  [rdi + 64], ymm2
VMOVDQA	yword  [rdi + 96], ymm3
VMOVDQA	yword  [rdi + 128], ymm4
VMOVDQA	yword  [rdi + 160], ymm5
VMOVDQA	yword  [rdi + 192], ymm6
VMOVDQA	yword  [rdi + 224], ymm7
lea	rdi, [rdi + 256]
lea	r9, [r9 + 256]
%endrep

%rep	N16_ % 8
VMOVDQA	ymm0, yword  [rdi]
vlddqu		ymm8, yword   [r9]
VPSUBW		ymm0, ymm0, ymm8
VPCMPGTW	ymm8, ymm12, ymm0
VPAND	ymm8, ymm8, ymm13
VPADDW	ymm0, ymm0, ymm8
VMOVDQA	yword  [rdi], ymm0
lea	rdi, [rdi + 32]
lea	r9, [r9 + 32]
%endrep

 lea	rsi, [rsi + 2]
 dec	ecx;
 jnz	%6
 
 

%endmacro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro for_plus 6
;count, plus_reg, result_reg, h_reg, predcalc_reg, for_label
mov	rdi, %3
mov	ecx, %1
; k = thread_pk_minus[i];
;mov	rsi, %2

;mov	r15, %5
;mov	r10, %4
; for (i = 0; i < thread_nums_plus; i++)
;if 0
%6:
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
VMOVDQA	ymm0, yword   [rdi]
VPSUBW	ymm0, ymm0, yword   [r15 + rbx]

 VPCMPGTW	ymm8, ymm12, ymm0
 VPAND		ymm8, ymm8, ymm13
 VPADDW		ymm0, ymm0, ymm8
 VMOVDQA	yword   [rdi], ymm0
 lea		rdi, [rdi + 32]

 ;for (j = 1; j <= N16_ / 8; j++)
 %rep	N16_ / 8
	; r0 = _mm256_sub_epi16(ck256[k], _mm256_lddqu_si256(cur_h256 + k));
	VMOVDQA	ymm0, yword  [rdi]
 VMOVDQA	ymm1, yword  [rdi + 32]
 VMOVDQA	ymm2, yword  [rdi + 64]
 VMOVDQA	ymm3, yword  [rdi + 96]
 VMOVDQA	ymm4, yword  [rdi + 128]
 VMOVDQA	ymm5, yword  [rdi + 160]
 VMOVDQA	ymm6, yword  [rdi + 192]
 VMOVDQA	ymm7, yword  [rdi + 224]
 
 vlddqu		ymm8, yword   [r9]
 vlddqu		ymm9, yword   [r9 + 32]
 vlddqu		ymm10, yword   [r9 + 64]
 vlddqu		ymm11, yword   [r9 + 96]
 
 VPSUBW		ymm0, ymm0, ymm8
 VPSUBW		ymm1, ymm1, ymm9
 VPSUBW		ymm2, ymm2, ymm10
 VPSUBW		ymm3, ymm3, ymm11

 vlddqu		ymm8, yword   [r9 + 128]
 vlddqu		ymm9, yword   [r9 + 160]
 vlddqu		ymm10, yword   [r9 + 192]
 vlddqu		ymm11, yword   [r9 + 224]
 
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

VMOVDQA	yword  [rdi], ymm0
VMOVDQA	yword  [rdi + 32], ymm1
VMOVDQA	yword  [rdi + 64], ymm2
VMOVDQA	yword  [rdi + 96], ymm3
VMOVDQA	yword  [rdi + 128], ymm4
VMOVDQA	yword  [rdi + 160], ymm5
VMOVDQA	yword  [rdi + 192], ymm6
VMOVDQA	yword  [rdi + 224], ymm7
lea	rdi, [rdi + 256]
lea	r9, [r9 + 256]
 %endrep

%rep	N16_ % 8

VMOVDQA	ymm0, yword  [rdi]
vlddqu		ymm8, yword   [r9]
VPSUBW		ymm0, ymm0, ymm8
VPCMPGTW	ymm8, ymm12, ymm0
VPAND	ymm8, ymm8, ymm13
VPADDW	ymm0, ymm0, ymm8
VMOVDQA	yword  [rdi], ymm0
lea	rdi, [rdi + 32]
lea	r9, [r9 + 32]

%endrep

 lea	rsi, [rsi + 2]
 dec	cx;
 jnz	%6
 ;endif

%endmacro
