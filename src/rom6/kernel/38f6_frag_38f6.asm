; ROM6 0x38F6 FRAG_38F6 -- 5w, symbols.yaml data_word.
; Evidence: Bound 38F6-38FA (5w; exit RET FC00@38FA byte-verified, exit scan clean; micro-span); entries bc F820@38EF->38F6 byte-verified (from ROUTINE_38C9 [38C9-38F5] interior) + post-RET he
; ORIGIN 0x38F6
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #24576,*(0xc)
	ld     b,a
	ret
