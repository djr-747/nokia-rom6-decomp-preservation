; ROM6 0xC965 ROUTINE_C965 -- 126w, symbols.yaml data_word.
; Evidence: Entry E723 F020 0100 F274 E54B; caller F274 @C90A; first-RET @C9E2; inner 2x calld E54B + RPT/RPTBD x5 + sub/saccd; HYPOTHESIS dsp-math worker.
; ORIGIN 0xC965
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @C965 e723 mvmm   ar2,ar3
	mvmm   ar2,ar3
	; @C966 f020 ld     #256,a
	ld     #256,a
	; @C968 f274 calld  0xe54b
	calld  0xe54b
	; @C96A ec27 rpt    #39
	rpt    #39
	; @C96B 3892 squra  *ar2+,a
	squra  *ar2+,a
	; @C96C f445 ld     a,5,a
	ld     a,5,a
	; @C96D 8265 sth    a,0x65
	sth    a,0x65
	; @C96E 7712 stm    #3314,ar2
	stm    #3314,ar2
	; @C970 f020 ld     #256,a
	ld     #256,a
	; @C972 f274 calld  0xe54b
	calld  0xe54b
	; @C974 ec27 rpt    #39
	rpt    #39
	; @C975 3892 squra  *ar2+,a
	squra  *ar2+,a
	; @C976 f445 ld     a,5,a
	ld     a,5,a
	; @C977 8264 sth    a,0x64
	sth    a,0x64
	; @C978 7712 stm    #3314,ar2
	stm    #3314,ar2
	; @C97A 7714 stm    #100,ar4
	stm    #100,ar4
	; @C97C 7715 stm    #3434,ar5
	stm    #3434,ar5
	; @C97E 7666 st     #32,0x66
	st     #32,0x66
	; @C980 7767 stm    #32767,103
	stm    #32767,103
	; @C982 771a stm    #39,brc
	stm    #39,brc
	; @C984 f272 rptbd  0xc994
	rptbd  0xc994
	; @C986 7716 stm    #4352,ar6
	stm    #4352,ar6
	; @C988 a40a mpy    *ar2,*ar4+,a
	mpy    *ar2,*ar4+,a
	; @C989 b096 mac    *ar3+,*ar4-,a
	mac    *ar3+,*ar4-,a
	; @C98A 0266 adds   0x66,a
	adds   0x66,a
	; @C98B f47a sfta   a,-6
	sfta   a,-6
	; @C98C 4567 ld     0x67,16,b
	ld     0x67,16,b
	.word 0xFD43 ; XC: gas encoder gap
	; @C98E f784 neg    b
	neg    b
	; @C98F cb0b st     b,*ar5+ || ld     *ar2,b
	st     b,*ar5+ || ld     *ar2,b
	.word 0xFF43 ; XC: gas encoder gap
	; @C991 f484 neg    a
	neg    a
	; @C992 f784 neg    b
	neg    b
	; @C993 8392 sth    b,*ar2+
	sth    b,*ar2+
	; @C994 8096 stl    a,*ar6+
	stl    a,*ar6+
	; @C995 7710 stm    #5,ar0
	stm    #5,ar0
	; @C997 7712 stm    #4396,ar2
	stm    #4396,ar2
	; @C999 7713 stm    #4184,ar3
	stm    #4184,ar3
	; @C99B 7714 stm    #4352,ar4
	stm    #4352,ar4
	; @C99D 7715 stm    #98,ar5
	stm    #98,ar5
	; @C99F 7716 stm    #4,ar6
	stm    #4,ar6
	; @C9A1 f020 ld     #-1,a
	ld     #-1,a
	; @C9A3 ec03 rpt    #3
	rpt    #3
	; @C9A4 808a stl    a,*ar2-
	stl    a,*ar2-
	; @C9A5 8082 stl    a,*ar2
	stl    a,*ar2
	; @C9A6 8085 stl    a,*ar5
	stl    a,*ar5
	; @C9A7 e741 mvmm   ar4,ar1
	mvmm   ar4,ar1
	; @C9A8 771a stm    #7,brc
	stm    #7,brc
	; @C9AA f272 rptbd  0xc9b1
	rptbd  0xc9b1
	; @C9AC 44d9 ld     *ar1+0%,16,a
	ld     *ar1+0%,16,a
	; @C9AD 4182 sub    *ar2,16,a,b
	sub    *ar2,16,a,b
	; @C9AE 9d1e srccd  *ar3,bgt
	srccd  *ar3,bgt
	; @C9AF 9e0e saccd  a,*ar2,bgt
	saccd  a,*ar2,bgt
	; @C9B0 44d9 ld     *ar1+0%,16,a
	ld     *ar1+0%,16,a
	; @C9B1 4182 sub    *ar2,16,a,b
	sub    *ar2,16,a,b
	; @C9B2 4592 ld     *ar2+,16,b
	ld     *ar2+,16,b
	; @C9B3 4285 sub    *ar5,16,b,a
	sub    *ar5,16,b,a
	; @C9B4 9fb6 saccd  b,*ar5+,agt
	saccd  b,*ar5+,agt
	; @C9B5 4516 ld     0x16,16,b
	ld     0x16,16,b
	; @C9B6 6e8e banzd  0xc9a7,*ar6-
	banzd  0xc9a7,*ar6-
	; @C9B8 9f76 saccd  b,*ar5-,agt
	saccd  b,*ar5-,agt
	; @C9B9 a49a mpy    *ar3+,*ar4+,a
	mpy    *ar3+,*ar4+,a
	; @C9BA e804 ld     #4,a
	ld     #4,a
	; @C9BB 0863 sub    0x63,a
	sub    0x63,a
	; @C9BC 8813 stlm   a,ar3
	stlm   a,ar3
	; @C9BD 7719 stm    #5,bk
	stm    #5,bk
	; @C9BF 7710 stm    #1,ar0
	stm    #1,ar0
	; @C9C1 771a stm    #4,brc
	stm    #4,brc
	; @C9C3 7712 stm    #4166,ar2
	stm    #4166,ar2
	; @C9C5 f272 rptbd  0xc9cb
	rptbd  0xc9cb
	; @C9C7 7714 stm    #4171,ar4
	stm    #4171,ar4
	; @C9C9 4413 ld     0x13,16,a
	ld     0x13,16,a
	; @C9CA e4d8 st     a,*ar2+ || ld     *ar3+0%,t
	st     a,*ar2+ || ld     *ar3+0%,t
	; @C9CB 8294 sth    a,*ar4+
	sth    a,*ar4+
	; @C9CC 7719 stm    #0,bk
	stm    #0,bk
	; @C9CE 7712 stm    #4184,ar2
	stm    #4184,ar2
	; @C9D0 770e stm    #5,t
	stm    #5,t
	; @C9D2 f162 ld     #7,16,b
	ld     #7,16,b
	; @C9D4 771a stm    #4,brc
	stm    #4,brc
	; @C9D6 ed0f ld     #15,asm
	ld     #15,asm
	; @C9D7 7710 stm    #2,ar0
	stm    #2,ar0
	; @C9D9 f272 rptbd  0xc9e0
	rptbd  0xc9e0
	; @C9DB 7713 stm    #0,ar3
	stm    #0,ar3
	; @C9DD 4282 sub    *ar2,16,b,a
	sub    *ar2,16,b,a
	; @C9DE f48c mpya   a
	mpya   a
	; @C9DF 0013 add    0x13,a
	add    0x13,a
	; @C9E0 c8d8 st     a,*ar2+ || ld     *ar3+0%,a
	st     a,*ar2+ || ld     *ar3+0%,a
	; @C9E1 ed00 ld     #0,asm
	ld     #0,asm
	; @C9E2 fc00 ret
	ret
