; ROM6 0x6596 FRAG_6596 -- 15w, symbols.yaml data_word.
; Evidence: Bound 6596-65A4 (15w; exit B F073@65A3->65AA + operand 65A4 — branch-tailed into FRAG_65AA head; exit scan otherwise clean); entry bc F84E@6587->6596 byte-verified (from FRAG_64F4)
; ORIGIN 0x6596
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #1,a,b
	bc     0x65aa,blt
	sub    #4,a,b
	bc     0x65aa,bgeq
	bitf   *(0x2627),#256
	bc     0x65b1,ntc
	b      0x65aa
