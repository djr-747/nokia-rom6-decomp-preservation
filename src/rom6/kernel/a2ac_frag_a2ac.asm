; ROM6 0xA2AC FRAG_A2AC -- 13w, symbols.yaml data_word.
; Evidence: Bound A2AC-A2B8 (13w; sole exit RET FC00@A2B8 byte-verified); BACC-table entry (A255 slot 4); zero callers; no interior uncond; out-calls A2C3/A3A3 + calld A2B9; HYPOTHESIS.
; ORIGIN 0xA2AC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xa3a3
	rc     bneq
	mvdk   *(0x22d),0x265b
	calld  0xa2b9
	stm    #-8776,ar5
	ret
