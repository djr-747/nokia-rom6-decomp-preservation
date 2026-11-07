; ROM6 0x4313 FRAG_4313 -- 2w, symbols.yaml data_word.
; Evidence: Bound 4313-4314 (2w micro: ld #0,a + RET FC00@4314, byte-verified; exit scan clean); entries B F073@42DA->4313 byte-verified (exterior from ROUTINE_42B8 [42B8-4312] interior, CODE)
; ORIGIN 0x4313
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	ret
