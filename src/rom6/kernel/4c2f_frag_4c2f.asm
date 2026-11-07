; ROM6 0x4C2F FRAG_4C2F -- 6w, symbols.yaml data_word.
; Evidence: Bound 4C2F-4C34 (6w micro-arm: sub #211 + bc + exit B F073@4C33->0702 + operand 4C34, byte-verified; exit scan clean); entry bc F84C@4C2B->4C2F byte-verified (chained from FRAG_4C2
; ORIGIN 0x4C2F
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #211,a,b
	bc     0x4c35,bneq
	b      0x702
