; ROM6 0x296A FRAG_296A -- 25w, symbols.yaml data_word.
; Evidence: Bound 296A-2982 (25w; exit F073@2981->283D + operand 2982); ext branch-entry bc F84C@27FC (corroborated STATE/FRAME-region entry, not F074-called); entry F074 05F8@296A (out-call, 
; ORIGIN 0x296A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5f8
	st     #4096,*ar2
	nop
	portw  *ar2,1
	rpt    #9
	nop
	stm    #9786,ar2
	bitf   *ar2,#96
	bc     0x2983,tc
	bitf   *(0x3ec8),#32
	bc     0x283d,ntc
	andm   #-1025,*(0x13d0)
	b      0x283d
