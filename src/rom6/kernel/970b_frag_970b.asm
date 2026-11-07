; ROM6 0x970B FRAG_970B -- 85w, symbols.yaml data_word.
; Evidence: Bound 970B-975F (85w; NO exit-class in-span — falls into 9760 zone; pre-word 0800 = retd delay of FRAG_9700, not post-RET — entries are branch-based); entries bcd FA20@96C3->970B b
; ORIGIN 0x970B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,intm
	portr  0,*ar2
	orm    #16,*ar2
	nop
	portw  *ar2,0
	rpt    #20
	nop
	st     #1792,*ar2
	nop
	portw  *ar2,1
	rpt    #18
	nop
	orm    #1,*ar4
	andm   #-2049,*ar4
	portr  2,*ar2
	bitf   *ar4,#2
	bc     0x9738,tc
	orm    #1024,*ar2
	andm   #-769,*ar2
	nop
	portw  *ar2,2
	nop
	portr  54,*ar2
	andm   #-2,*ar2
	nop
	portw  *ar2,54
	call   0x97dd
	rete
	orm    #1536,*ar2
	andm   #-257,*ar2
	nop
	portw  *ar2,2
	nop
	portr  54,*ar2
	orm    #1,*ar2
	nop
	portw  *ar2,54
	call   0x97dd
	ld     *(0x2200),a
	rsbx   st1,intm
	rc     aneq
	ssbx   st1,intm
	stm    #96,ar2
	portr  2,*ar2
	andm   #-513,*ar2
	nop
	portw  *ar2,2
	nop
	portr  54,*ar2
	andm   #-2,*ar2
	nop
	portw  *ar2,54
	rete
