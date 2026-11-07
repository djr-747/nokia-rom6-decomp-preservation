; ROM6 0x5755 ROUTINE_5755 -- 25w, symbols.yaml data_word.
; Evidence: Bound 5755-576D (25w; exit RET FC00@576D byte-verified, exit scan clean); entries cc F920@5207-> 5755 byte-verified (exterior) + post-RET head (FC00@5754); interior out-calls call@
; ORIGIN 0x5755
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	ld     *(0x250f),b
	and    #240,b
	sub    #48,b,a
	rc     aeq
	sub    #16,b,a
	bc     0x576e,aneq
	ld     *(0x2642),a
	sub    *(0x915),a
	rc     aneq
	calld  0x6993
	stm    #2326,ar1
	bc     0x5785,aeq
	ret
