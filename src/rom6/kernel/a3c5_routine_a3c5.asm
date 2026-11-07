; ROM6 0xA3C5 ROUTINE_A3C5 -- 9w, symbols.yaml data_word.
; Evidence: Bound A3C5-A3CD (exit RET FC00@A3CD objdump); callers F074 @AFC6/@B134 (B134 objdump-verified call 0xa3c5); interior call A3D5 + ccd 39A4@A3C9; HYPOTHESIS.
; ORIGIN 0xA3C5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa3d5
	stm    #2324,ar2
	ccd    0x39a4,aneq
	stm    #9492,ar3
	ret
