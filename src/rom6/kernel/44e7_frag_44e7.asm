; ROM6 0x44E7 FRAG_44E7 -- 22w, symbols.yaml data_word.
; Evidence: Bound 44E7-44FC (22w; exit RET FC00@44FC byte-verified); post-RET head (FC00@44E6); interior out-calls call@44E7->2E2F + calld@44F8->2C88; chain link; HYPOTHESIS.
; ORIGIN 0x44E7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	stm    #12032,ar2
	mvmm   ar2,ar3
	st     #4096,*ar2+
	mvkd   0x54e,*ar2+
	ld     *(0x22d),8,a
	or     *(0x2623),a
	stl    a,*ar2
	stm    #116,ar4
	calld  0x2c88
	stm    #6,ar5
	ret
