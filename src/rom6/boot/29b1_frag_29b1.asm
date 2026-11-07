; ROM6 0x29B1 FRAG_29B1 -- 8w, symbols.yaml data_word.
; Evidence: Bound 29B1-29B8 (8w; TRIMMED from 29B1-2A72 draft at first-outside B F073@29B7->2A8A + operand 29B8 per ordered-scan rule; remaining outside-targeting F073s 29D1-2A71 fall in dark 
; ORIGIN 0x29B1
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #2,*ar3
	stm    #4724,ar3
	stm    #4718,ar2
	b      0x2a8a
