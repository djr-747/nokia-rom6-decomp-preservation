; ROM6 0xB146 FRAG_B146 -- 5w, symbols.yaml data_word.
; Evidence: Bound B146-B14A (5w, exit FC00@B14A); bacc-table arm; calld-stub; HYPOTHESIS.
; ORIGIN 0xB146
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8664,ar5
	ret
