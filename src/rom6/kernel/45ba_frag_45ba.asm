; ROM6 0x45BA FRAG_45BA -- 8w, symbols.yaml data_word.
; Evidence: Bound 45BA-45C1 (8w; exit RET FC00@45C1 byte-verified); post-RET head (FC00@45B9); head 7714 04FA; no interior ops; chain link; HYPOTHESIS.
; ORIGIN 0x45BA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1274,ar4
	andm   #-3,*ar4
	xc     2,beq
	orm    #2,*ar4
	ret
