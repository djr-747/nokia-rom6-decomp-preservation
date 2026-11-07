; ROM6 0xA25F FRAG_A25F -- 5w, symbols.yaml data_word.
; Evidence: Bound A25F-A263 (5w, exit FC00@A263 byte-verified); bacc-table arm entry (table slot 1); body F274 A2B9 + stm + ret; HYPOTHESIS.
; ORIGIN 0xA25F
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8805,ar5
	ret
