; ROM6 0x3D1B FRAG_3D1B -- 32w, symbols.yaml data_word.
; Evidence: Bound 3D1B-3D3A (32w; exit RET FC00@3D3A byte-verified, exit scan clean); post-RET head only (FC00@3D1A, zero exterior refs); no interior joins; tail 3D3B-3D78 stays dark; HYPOTHES
; ORIGIN 0x3D1B
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #2,*ar3
	stm    #4724,ar3
	stm    #4718,ar2
	nop
	portw  *ar2+,48
	nop
	nop
	portw  *ar3+,49
	nop
	nop
	portw  *ar3+,50
	nop
	nop
	portw  *ar2,4
	rpt    #17
	nop
	mvdk   *ar2+,0x58e
	addm   #-2,*(0x2660)
	addm   #-2,*(0x265e)
	ret
