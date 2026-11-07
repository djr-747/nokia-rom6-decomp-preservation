; ROM6 0x7A4B FRAG_7A4B -- 16w, symbols.yaml data_word.
; Evidence: Bound 7A4B-7A5A (16w; exit F073@7A59->7A61 + operand 7A5A, single exit-class word, byte-verified); entry bc F820@7A42->7A4B byte-verified (cond); interior clean of RET/FE00/BD/BACC
; ORIGIN 0x7A4B
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x34bf),#0
	bc     0x7a5b,tc
	cmpm   *(0x34bf),#2
	bc     0x7a5b,tc
	mvkd   0x34ca,*ar4
	stm    #13502,ar3
	b      0x7ab0
