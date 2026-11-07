; ROM6 0xDA40 FRAG_DA40 -- 8w, symbols.yaml data_word.
; Evidence: Bound DA40-DA47 (8w; exit RET FC00@DA47 byte-verified, first and only unconditional exit-class; exit scan clean); entry bc F842@DA3B->DA40 byte-verified (cond ageq, exterior from F
; ORIGIN 0xDA40
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #4,a
	and    0x5a,a
	st     #13,0x5a
	xc     2,aeq
	st     #5,0x5a
	ret
