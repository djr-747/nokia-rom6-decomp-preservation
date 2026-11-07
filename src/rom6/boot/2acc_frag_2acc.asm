; ROM6 0x2ACC FRAG_2ACC -- 48w, symbols.yaml data_word.
; Evidence: Bound 2ACC-2AFB (exit F073@2AFA->283D + operand 2AFB; exit scan clean of RET/FE00/BD/BACC); entry bc F830@298C->2ACC byte-verified (live FRAG_2983 tail); entries into 2ACD-2AFB int
; ORIGIN 0x2ACC
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0x265e,ar2
	mvdm   0x2660,ar3
	bitf   *ar2,#4
	bc     0x2ae6,tc
	ld     *(0x3e81),b
	sub    *ar3,b
	portr  12,*(0x8)
	or     *(0x3ecd),a
	bc     0x2ae2,beq
	ld     *(0x3ecd),b
	cmpl   b
	and    b,a
	nop
	portw  *(0x8),12
	nop
	portw  *ar2+,48
	nop
	nop
	portw  *ar2+,4
	rpt    #22
	nop
	nop
	portw  *ar3+,49
	nop
	nop
	portw  *ar3+,50
	mvmd   ar2,0x265e
	mvmd   ar3,0x2660
	b      0x283d
