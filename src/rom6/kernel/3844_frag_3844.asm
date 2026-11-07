; ROM6 0x3844 FRAG_3844 -- 5w, symbols.yaml data_word.
; Evidence: Bound 3844-3848 (5w micro-arm: st #2076 + exit B F073@3847->3850 + operand 3848, byte-verified; exit scan clean); entry bc F84D@3837->3844 byte-verified (chained from FRAG_382E int
; ORIGIN 0x3844
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #2076,*(0x2202)
	b      0x3850
