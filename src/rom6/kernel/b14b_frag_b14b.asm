; ROM6 0xB14B FRAG_B14B -- 12w, symbols.yaml data_word.
; Evidence: Bound B14B-B156 (12w, exit FC00@B156); bacc-table arm; HYPOTHESIS.
; ORIGIN 0xB14B
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8652,ar5
	st     #0,*(0x9c6)
	calld  0xa2b9
	stm    #-8641,ar5
	ret
