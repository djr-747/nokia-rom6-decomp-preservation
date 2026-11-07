; ROM6 0x7140 FRAG_7140 -- 2w, symbols.yaml data_word.
; Evidence: Bound 7140-7141 (2w micro: rsbx st0,tc + RET FC00@7141, byte-verified; exit scan clean); entries B F073@713A->7140 byte-verified (exterior from FLAG_GATE_712D [712D-713F] interior,
; ORIGIN 0x7140
	.sect ".text"
	.mmregs
	.global _start
_start:
	rsbx   st0,tc
	ret
