; ROM6 0x44D7 FRAG_44D7 -- 16w, symbols.yaml data_word.
; Evidence: Bound 44D7-44E6 (16w; exit RET FC00@44E6 byte-verified); post-RET head (FC00@44D6); interior out-calls call@44D7->2E2F + calld@44E2->2C88; chain link; HYPOTHESIS.
; ORIGIN 0x44D7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	stm    #12032,ar3
	ld     #13,8,a
	or     *(0x568),a
	stm    #116,ar4
	stl    a,*ar3
	calld  0x2c88
	stm    #2,ar5
	ret
