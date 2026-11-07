; ROM6 0x64A0 SUB85_644B -- 84w (overlap-split wave-12).
; Evidence: Words 64A0-64F3 (entry cmpm *(0x8),#82 @64A0; exits/branches per @-comments in body). Word 649F (0x676A) owned by 649d_frag_649d.asm as its branch operand (assemblability forces single owner; was leading bare .word here). ZERO true CALLers (sole ref FA20 bcd ntc @6419). Recombine-clean.
; ORIGIN 0x64A0
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @64A0 60f8 cmpm   *(0x8),#82
	cmpm   *(0x8),#82
	; @64A3 f820 bc     0x64ae,ntc
	bc     0x64ae,ntc
	; @64A5 f074 call   0x687f
	call   0x687f
	; @64A7 f84c bc     0x676a,bneq
	bc     0x676a,bneq
	; @64A9 f074 call   0x68a2
	call   0x68a2
	; @64AB 8185 stl    b,*ar5
	stl    b,*ar5
	; @64AC f073 b      0x676a
	b      0x676a
	; @64AE 60f8 cmpm   *(0xb),#16
	cmpm   *(0xb),#16
	; @64B1 f820 bc     0x670d,ntc
	bc     0x670d,ntc
	; @64B3 60f8 cmpm   *(0x8),#26
	cmpm   *(0x8),#26
	; @64B6 f830 bc     0x670d,tc
	bc     0x670d,tc
	; @64B8 f074 call   0x598
	call   0x598
	; @64BA 7712 stm    #1359,ar2
	stm    #1359,ar2
	; @64BC 6182 bitf   *ar2,#1024
	bitf   *ar2,#1024
	; @64BE f820 bc     0x64f6,ntc
	bc     0x64f6,ntc
	; @64C0 7711 stm    #907,ar1
	stm    #907,ar1
	; @64C2 7715 stm    #1348,ar5
	stm    #1348,ar5
	; @64C4 11f8 ld     *(0x2fd7),b
	ld     *(0x2fd7),b
	; @64C6 09f8 sub    *(0x565),b
	sub    *(0x565),b
	; @64C8 1081 ld     *ar1,a
	ld     *ar1,a
	; @64C9 f844 bc     0x64d8,aneq
	bc     0x64d8,aneq
	; @64CB f84c bc     0x64f6,bneq
	bc     0x64f6,bneq
	; @64CD 13f8 ldu    *(0x2fd8),b
	ldu    *(0x2fd8),b
	; @64CF f230 and    #7,b,a
	and    #7,b,a
	; @64D1 f844 bc     0x64f6,aneq
	bc     0x64f6,aneq
	; @64D3 7681 st     #1,*ar1
	st     #1,*ar1
	; @64D5 8185 stl    b,*ar5
	stl    b,*ar5
	; @64D6 f073 b      0x64e8
	b      0x64e8
	; @64D8 12f8 ldu    *(0x2fd8),a
	ldu    *(0x2fd8),a
	; @64DA ff4b xc     2,blt (bare word: hand-encoded per original draft)
	.word 0xFF4B ; xc 2,blt
	; @64DB f010 sub    #1,a
	sub    #1,a
	; @64DD 0885 sub    *ar5,a
	sub    *ar5,a
	; @64DE f842 bc     0x64e2,ageq
	bc     0x64e2,ageq
	; @64E0 f000 add    #-12288,a
	add    #-12288,a
	; @64E2 f030 and    #-1,a
	and    #-1,a
	; @64E4 f0fd sftl   a,-3
	sftl   a,-3
	; @64E5 f000 add    #1,a
	add    #1,a
	; @64E7 8081 stl    a,*ar1
	stl    a,*ar1
	; @64E8 1081 ld     *ar1,a
	ld     *ar1,a
	; @64E9 08f8 sub    *(0x38c),a
	sub    *(0x38c),a
	; @64EB f847 bc     0x64f4,aleq
	bc     0x64f4,aleq
	; @64ED 76f8 st     #0,*(0x545)
	st     #0,*(0x545)
	; @64F0 f273 bd     0x64f6
	bd     0x64f6
	; @64F2 6882 andm   #-1025,*ar2
	andm   #-1025,*ar2

