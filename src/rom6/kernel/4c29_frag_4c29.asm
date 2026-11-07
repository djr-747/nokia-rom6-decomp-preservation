; ROM6 0x4C29 FRAG_4C29 -- 6w, symbols.yaml data_word.
; Evidence: Bound 4C29-4C2E (6w micro-arm: sub #213 + bc + exit B F073@4C2D->0700 + operand 4C2E, byte-verified; exit scan clean); entry bc F84C@4BD9->4C29 byte-verified (cond bneq, exterior f
; ORIGIN 0x4C29
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #213,a,b
	bc     0x4c2f,bneq
	b      0x700
