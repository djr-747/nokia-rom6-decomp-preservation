; ROM6 0xA3CE FRAG_A3CE -- 7w, symbols.yaml data_word.
; Evidence: Bound A3CE-A3D4 (7w; exit RET FC00@A3D4 byte-verified, exit scan clean; minimal cell per 3616 precedent); post-RET head (FC00@A3CD = ROUTINE_A3C5 exit, CODE); zero exterior refs; A
; ORIGIN 0xA3CE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa3d5
	ccd    0x39f0,aneq
	stm    #1235,ar2
	ret
