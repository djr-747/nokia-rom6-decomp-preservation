; ROM6 0x4590 ROUTINE_4590 -- 16w, symbols.yaml data_word.
; Evidence: Bound 4590-459F (16w; exit RET FC00@459F byte-verified, exit scan clean); 10 callers byte-verified: 6x F074 @2D8C/2EC9/43D0/4AE1/7C99/7FFF + 4x cc F945 @7D7D/8041/80A8/811A ->4590;
; ORIGIN 0x4590
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	stm    #12517,ar3
	st     #12800,*ar3+
	or     #1,8,b
	stl    b,*ar3-
	stm    #4,ar5
	calld  0x2c88
	stm    #116,ar4
	ret
