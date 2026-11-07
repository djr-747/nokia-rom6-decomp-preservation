; ROM6 0x45B2 FRAG_45B2 -- 8w, symbols.yaml data_word.
; Evidence: Bound 45B2-45B9 (8w; exit RET FC00@45B9 byte-verified); post-RET head (FC00@45B1); head 7713 04FA; no interior ops; chain link; HYPOTHESIS.
; ORIGIN 0x45B2
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1274,ar3
	andm   #-2,*ar3
	xc     2,aeq
	orm    #1,*ar3
	ret
