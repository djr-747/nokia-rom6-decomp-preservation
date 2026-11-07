; ROM6 0xB141 FRAG_B141 -- 5w, symbols.yaml data_word.
; Evidence: Bound B141-B145 (5w, exit FC00@B145); bacc-table arm; calld-stub; HYPOTHESIS.
; ORIGIN 0xB141
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8676,ar5
	ret
