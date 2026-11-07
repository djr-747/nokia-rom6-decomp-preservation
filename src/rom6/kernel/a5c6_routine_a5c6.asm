; ROM6 0xA5C6 ROUTINE_A5C6 -- 12w, symbols.yaml data_word.
; Evidence: Bound A5C6-A5D1 (12w; exit RET FC00@A5D1 byte-verified, exit scan clean); entries single call F074@A273->A5C6 byte-verified (weak single-caller, flagged) + post-RET head (FC00@A5C5
; ORIGIN 0xA5C6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65a
	ld     *(0x262d),a
	rc     aeq
	ld     #0,b
	call   0x4ba8
	st     #0,*(0x262d)
	ret
