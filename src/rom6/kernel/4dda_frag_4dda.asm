; ROM6 0x4DDA FRAG_4DDA -- 8w, symbols.yaml data_word.
; Evidence: Bound 4DDA-4DE1 (8w, exit BD F273@4DDE->4E00 + delays); post-baccd head (4DA7-span ends 4DD9); zero refs; chain-link 1/5; not the killed 4DA7-4DDB draft; target 4E00 inside FRAG_4D
; ORIGIN 0x4DDA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8,bk
	stm    #6,ar1
	bd     0x4e00
	mar    *+ar3(0x2)%
