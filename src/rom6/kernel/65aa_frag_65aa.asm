; ROM6 0x65AA FRAG_65AA -- 68w, symbols.yaml data_word.
; Evidence: Bound 65AA-65ED (exit F273 bd@65EA->676A + operand/delays 65EB-65ED; TRIMMED from team 6656: parent byte-check found two unconditional early-outs F273@65EA/65F6->676A); callers are
; ORIGIN 0x65AA
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #1,a
	add    *(0x38b),a
	stl    a,*(0x60)
	call   0x692c
	stm    #1380,ar0
	stm    #1381,ar1
	ld     #51,b
	calld  0x6961
	stm    #12247,ar2
	stl    b,*(0x2fdc)
	bitf   *(0x51e),#2048
	stlm   a,ar4
	bc     0x65cc,tc
	sub    #51,a
	bc     0x65c2,ageq
	add    *ar6,a,b
	ldm    ar4,a
	nop
	xc     1,bgeq
	ld     #0,a
	ld     *ar5,b
	min    a
	stl    a,*ar5
	stm    #1309,ar2
	stm    #1359,ar0
	ld     *ar0,b
	and    #32,b,a
	bc     0x65ee,aeq
	and    #-33,b
	stl    b,*ar0
	ld     *(0x50d),16,a
	bitf   *(0x3ec8),#16
	mvdm   0x58b,t
	xc     2,ntc
	stm    #5,t
	mpya   b
	stl    b,*(0x50b)
	orm    #256,*ar2
	bd     0x676a
	st     #0,*ar5
