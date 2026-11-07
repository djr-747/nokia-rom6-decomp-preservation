; ROM6 0x2B45 FRAG_2B45 -- 14w, symbols.yaml data_word.
; Evidence: Bound 2B45-2B52 (14w; exit F073@2B51->2E64 + operand 2B52, single exit-class word, byte-verified); entries 2x bc F84C@282B/282F->2B45 byte-verified (cond pair); interior F84C@2B4A 
; ORIGIN 0x2B45
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x64e
	st     #64,*ar2
	nop
	portw  *ar2,1
	rpt    #13
	nop
	orm    #8192,*(0x552)
	b      0x283d
