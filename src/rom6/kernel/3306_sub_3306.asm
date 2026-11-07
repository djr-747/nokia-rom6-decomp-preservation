; ROM6 0x3306 SUB_3306 -- 54w, symbols.yaml program_word.
; Evidence: Bound 3306-333B (54w); entry TRACE (same histogram: 3306-333A heads x2, banz 3338->332F loop x64); exits b F073@333A->335C; HYPOTHESIS.
; ORIGIN 0x3306
	.sect ".text"
	.global _start
_start:
	stm    #9767,ar5
	orm    #16,*ar5
	stm    #9785,ar4
	bitf   *ar2,#-32768
	andm   #-2,*ar4
	xc     2,tc
	orm    #1,*ar4
	bitf   *(0x3ec8),#16
	bc     0x333c,ntc
	bitf   *ar2,#16384
	andm   #-7169,*(0x263a)
	bc     0x3322,ntc
	orm    #6144,*(0x263a)
	ld     *ar2+%,-8,a
	and    #63,a
	stl    a,*(0x2655)
	stm    #949,ar4
	st     #0,*(0x588)
	stm    #31,ar3
	ld     *ar2+0%,a
	sub    #-1,a,b
	bc     0x3338,beq
	addm   #1,*(0x588)
	stl    a,*ar4+
	banz   0x332f,*ar3-
	b      0x335c
