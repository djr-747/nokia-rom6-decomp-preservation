; ROM6 0xAEA0 FRAG_AEA0 -- 8w, symbols.yaml data_word.
; Evidence: Bound AEA0-AEA7 (8w; exit RETD FE00@AEA5 + delays AEA6-AEA7 (mvmd 2w), byte-verified; exit scan clean); entry bc F830@AE8C->AEA0 byte-verified (cond tc, thin dark-src from unclaime
; ORIGIN 0xAEA0
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0x265e,ar3
	nop
	mar    *+ar3(0xfffe)
	retd
	mvmd   ar3,0x265e
