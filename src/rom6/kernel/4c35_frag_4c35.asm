; ROM6 0x4C35 FRAG_4C35 -- 6w, symbols.yaml data_word.
; Evidence: Bound 4C35-4C3A (6w micro-arm: sub #217 + bc + exit B F073@4C39->0704 + operand 4C3A, byte-verified; exit scan clean); entry bc F84C@4C31->4C35 byte-verified (chained from FRAG_4C2
; ORIGIN 0x4C35
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #217,a,b
	bc     0x4c3b,bneq
	b      0x704
