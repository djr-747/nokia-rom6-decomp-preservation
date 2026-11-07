; ROM6 0xB157 FRAG_B157 -- 5w, symbols.yaml data_word.
; Evidence: Bound B157-B15B (5w, exit FC00@B15B); bacc-table arm; calld-stub; abuts LEAF_B15C; HYPOTHESIS.
; ORIGIN 0xB157
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8636,ar5
	ret
