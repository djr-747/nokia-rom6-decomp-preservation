; ROM6 0xC806 FRAG_C806 -- 75w, symbols.yaml data_word.
; Evidence: Bound C806-C850 (75w; exit B F073@C84F->283D + operand C850 — branch-tailed outside; interior join B F073@C83C->C84B in-span; exit scan otherwise clean; pre-word 283D not post-RET 
; ORIGIN 0xC806
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ee
	ld     #256,a
	nop
	portw  *(0x8),1
	rpt    #7
	nop
	stm    #1308,ar2
	stm    #8437,ar3
	stm    #8436,ar5
	stm    #8435,ar6
	cmpm   *ar3,#0
	bc     0xc82a,ntc
	ld     *ar6,a
	stl    a,*ar5
	and    #512,a,b
	and    #1024,a
	andm   #-3073,*ar2
	xc     2,bneq
	orm    #1024,*ar2
	xc     2,aneq
	orm    #2048,*ar2
	ld     *ar3,b
	bitf   *ar5,#512
	bcd    0xc83e,ntc
	addm   #1,*ar3
	sub    #250,b
	bc     0xc83e,bneq
	ld     *ar5,-8,a
	sfta   a,8
	or     #250,a
	st     #0,*ar3
	b      0xc84b
	ld     *(0x20f9),a
	bc     0x283d,aeq
	sub    #1,a
	stl    a,*(0x20f9)
	stm    #8439,ar2
	ld     *ar2(0x1),a
	delay  *ar2
	nop
	portw  *(0x8),52
	b      0x283d
