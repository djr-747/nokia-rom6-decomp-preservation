; ROM6 0x5E7D SUB_5E7D -- 54w, symbols.yaml data_word.
; Evidence: Bound 5E7D-5EB2 (exit F073@5EB1->5EB5 + operand); caller F074@5D81; HYPOTHESIS.
; ORIGIN 0x5E7D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	stm    #9767,ar2
	bitf   *ar2,#1
	bc     0x5ee1,ntc
	ld     #0,b
	bitf   *(0x2627),#128
	bc     0x5e96,tc
	ld     *(0x2634),a
	bc     0x5ee1,alt
	bitf   *(0x2629),#-32768
	bc     0x5ee1,tc
	ld     #256,b
	andm   #-130,*ar2+
	andm   #8191,*ar2+
	andm   #8191,*ar2
	st     #0,*(0x2614)
	stm    #9302,ar2
	stm    #12042,ar3
	or     *ar2+,b
	stl    b,*ar3+
	mvdd   *ar2,*ar3+
	mvkd   0x2618,*ar3+
	mvkd   0x2615,*ar3
	cmpm   *(0x250f),#34
	bc     0x5eb3,ntc
	addm   #3750,*ar3+
	b      0x5eb5
