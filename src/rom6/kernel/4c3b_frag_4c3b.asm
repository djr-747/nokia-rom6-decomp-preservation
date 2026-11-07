; ROM6 0x4C3B FRAG_4C3B -- 6w, symbols.yaml data_word.
; Evidence: Bound 4C3B-4C40 (6w micro-arm: sub #219 + bc + exit B F073@4C3F->0706 + operand 4C40, byte-verified; exit scan clean); entry bc F84C@4C37->4C3B byte-verified (chained from FRAG_4C3
; ORIGIN 0x4C3B
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #219,a,b
	bc     0x4c41,bneq
	b      0x706
