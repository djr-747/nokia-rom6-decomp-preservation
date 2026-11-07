; ROM6 0xCF01 ROUTINE_CF01 -- 36w, symbols.yaml data_word.
; Evidence: Bound CF01-CF24 (36w; exit RET FC00@CF24 byte-verified, exit scan clean); entries call F074@AA2C-> CF01 byte-verified head-exact, far exterior (DROM zone); pre-word 1466 (retd dela
; ORIGIN 0xCF01
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,dp
	stm    #0,bk
	pshm   st1
	stm    #1856,st1
	call   0x680
	stm    #3394,ar1
	stm    #-615,ar3
	calld  0xe276
	stm    #4362,ar4
	stm    #-375,ar2
	calld  0xe2b4
	stm    #4364,ar3
	calld  0xe2c3
	stm    #3867,ar1
	st     #3170,0x63
	st     #3986,0x62
	calld  0xe395
	st     #3867,0x11
	popm   st1
	ret
