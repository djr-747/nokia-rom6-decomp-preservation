; ROM6 0x3273 SUB_3273A -- 65w, symbols.yaml program_word.
; Evidence: Bound 3273-32B3 (63w); entry TRACE (same histogram: 3273 head x8, contiguous through 32B2); lane head of dispatch loop; exits b F073@32B2->2E64; HYPOTHESIS.
; ORIGIN 0x3273
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x3ec8),#32
	ld     *ar2+%,5,a
	stlm   a,ar5
	xc     2,ntc
	add    #12632,a
	xc     2,tc
	add    #4816,a
	stlm   a,ar4
	nop
	rpt    #31
	mvdd   *ar2+0%,*ar4+
	call   0x2e2f
	ldm    ar5,a
	sub    #96,a
	bc     0x2e64,aneq
	ssbx   st1,intm
	portr  33,*(0xb)
	or     #5,b
	and    #-3,b
	nop
	portw  *(0xb),33
	bitf   *(0x3ec8),#32
	stm    #12632,ar3
	xc     2,tc
	stm    #4816,ar3
	stm    #127,brc
	rptb   0x32a5
	nop
	portw  *ar3+,36
	nop
	portr  33,*(0xb)
	and    #-5,b
	or     #3,b
	nop
	portw  *(0xb),33
	rsbx   st1,intm
	b      0x2e64
