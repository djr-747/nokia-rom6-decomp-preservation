; ROM6 0x375E FRAG_375E -- 23w, symbols.yaml data_word.
; Evidence: Bound 375E-3774 (23w; exit B F073@3773->2E64 + operand 3774, byte-verified; exit scan clean); entry bc F820@3756->375E byte-verified (chained from FRAG_3753 interior); dispatcher-c
; ORIGIN 0x375E
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x8),#20
	bc     0x3775,ntc
	call   0x2e2f
	stm    #10217,ar3
	stm    #158,ar4
	stm    #4,ar5
	st     #21,*ar3+
	st     #18,*ar3+
	stm    #10217,ar3
	call   0x2c88
	b      0x2e64
