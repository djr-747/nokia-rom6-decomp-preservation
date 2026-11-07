; ROM6 0xB04B FRAG_B04B -- 5w, symbols.yaml data_word.
; Evidence: Bound B04B-B04F (5w, exit FC00@B04F); post-RET head (after FC00@B04A); HYPOTHESIS.
; ORIGIN 0xB04B
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8734,ar5
	ret
