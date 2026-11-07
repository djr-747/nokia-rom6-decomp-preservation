; ROM6 0x3BFE FRAG_3BFE -- 2w, symbols.yaml data_word.
; Evidence: Bound 3BFE-3BFF (2w micro: ssbx st0,tc + RET FC00@3BFF, byte-verified; exit scan clean); entries 5x B F073@3BE7/3BEC/3BF1/3BF6/3BFB->3BFE byte-verified (all from CMPM_GATE_CHAIN [3
; ORIGIN 0x3BFE
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st0,tc
	ret
