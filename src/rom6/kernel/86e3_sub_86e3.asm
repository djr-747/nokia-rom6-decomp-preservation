; ROM6 0x86E3 SUB_86E3 -- 24w, symbols.yaml data_word.
; Evidence: Bound 86E3-86FA (24w; exit FC00@86FA); 4x ext CALLD F074... F274 @8670/8897/9CC8/A73C (all byte- verified calld 0x86e3); head F074 0590 F6B8; F072@86ED role open (verbatim); HYPOTH
; Pool: BITT T-test + ROLTC rotate-with-carry (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0x86E3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	rsbx   st1,sxm
	stm    #16,ar5
	stm    #-19903,ar1
	stm    #15,brc
	ldm    ar3,a
	rptb   0x86f5
	add    *ar1,-8,a
	stlm   a,ar2
	ld     *ar1+,t
	ldm    ar3,a
	bitt   *ar2
	roltc  b
	stl    b,*ar4+
	banz   0x86ea,*ar5-
	ssbx   st1,sxm
	ret
