; ROM6 0x63DA CMPD_63DA -- 99w, symbols.yaml data_word.
; Evidence: Entry 4481 7712 2614; tretd/orm flag body; mid-label 0x640F (F074-called @0x5DEF); branch-out FA20 644B @0x6419; bound 63DA-643C (ret @0x643D owned by the 643D span, fall-through abut, overlap-corrected wave-12; 62F2 ends retd 0x63D7 per a
; ORIGIN 0x63DA
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar1,16,a
	stm    #9748,ar2
	cmpm   *ar2,#4
	bc     0x63f7,ntc
	sub    *ar5,16,a
	bc     0x63f0,aneq
	orm    #8192,*ar0
	orm    #1,*(0x2627)
	st     #-13,*ar7
	stl    a,*(0x232)
	retd
	stl    a,*(0x55c)
	ld     *ar7,a
	rc     ageq
	addm   #1,*ar7
	retd
	orm    #16384,*ar0
	cmpm   *ar2,#2
	rc     ntc
	sub    *ar5,16,a,b
	bc     0x6404,bneq
	bitf   *(0x2628),#128
	rc     ntc
	retd
	orm    #16,*ar0
	sub    #50,16,a,b
	add    #1,16,a
	xc     1,beq
	ld     b,a
	sub    *ar5,16,a
	rc     aneq
	retd
	orm    #128,*ar0
	call   0x598
	stm    #16073,ar6
	ld     #240,a
	and    *(0x250f),a
	cmpm   *(0x8),#32
	bcd    0x644b,ntc
	stm    #12254,ar5
	bitf   *(0x54f),#128
	bc     0x676a,tc
	cmpm   *(0x53c),#2
	bc     0x643e,ntc
	stm    #1341,ar1
	ld     #104,b
	calld  0x6973
	stm    #2328,ar2
	sub    #5,b
	rc     bgeq
	call   0x697f
	stm    #9751,ar1
	stm    #1341,ar2
	ld     *ar2,a
	stl    a,*ar1
	sub    #26,a
	bc     0x6438,ageq
	; ret @0x643D owned by the 643D span (fall-through abut, overlap-corrected wave-12)
