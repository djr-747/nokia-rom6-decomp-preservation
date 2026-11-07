; ROM6 0x877D SUB_877D -- 70w, symbols.yaml data_word.
; Evidence: Bound 877D-87C2 (exit FC00@87C2); callers F074 @A754/@A95A (call 0x877d); out-calls 878B/87A7/87B1 (all CD, incl. recursion to 872B); preceded by FC00@877C; HYPOTHESIS.
; ORIGIN 0x877D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	stm    #1309,ar4
	bit    *ar4,13
	bc     0x87c3,ntc
	andm   #-5,*ar4
	cmpm   *(0x9c7),#0
	bc     0x87c3,ntc
	calld  0x872b
	stm    #2504,ar4
	ld     *(0x9cd),b
	and    #7,11,b
	sub    a,b
	bc     0x87c3,bneq
	cmpm   *(0x573),#-20196
	bc     0x87bf,tc
	ld     *(0x51c),a
	and    #4099,a
	add    *(0x3083),a
	bc     0x87bf,aneq
	stm    #-19631,ar1
	stm    #2504,ar4
	calld  0x87c7
	stm    #5,brc
	sub    *(0x575),a
	bc     0x87c3,alt
	stm    #3,ar6
	calld  0x87c7
	stm    #6,brc
	sub    #120,a,b
	bc     0x87c3,bgt
	sub    #40,a
	bc     0x87c3,alt
	banz   0x87b1,*ar6-
	st     #0,*(0x3082)
	ret
