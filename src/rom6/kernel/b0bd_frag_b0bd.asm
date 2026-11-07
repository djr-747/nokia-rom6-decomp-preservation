; ROM6 0xB0BD FRAG_B0BD -- 5w, symbols.yaml data_word.
; Evidence: Bound B0BD-B0C1 (5w, exit FC00@B0C1); post-RET head (after FC00@B0BC); HYPOTHESIS.
; ORIGIN 0xB0BD
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8702,ar5
	ret
