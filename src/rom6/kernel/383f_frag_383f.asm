; ROM6 0x383F FRAG_383F -- 5w, symbols.yaml data_word.
; Evidence: Bound 383F-3843 (5w micro-arm: st #2048 + exit B F073@3842->3850 + operand 3843, byte-verified; exit scan clean); entry bc F84D@3833->383F byte-verified (chained from FRAG_382E int
; ORIGIN 0x383F
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #2048,*(0x2202)
	b      0x3850
