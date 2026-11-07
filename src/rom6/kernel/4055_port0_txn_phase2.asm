; ROM6 0x4055 PORT0_TXN_PHASE2 -- 1w, symbols.yaml program_word.
; Evidence: Label inside PORT0_TXN, not an entry. Second pa0 strobe, 0x3EB5 retest, CALL 0x40A1 pairs, pa44 write, RC/RET.
; ORIGIN 0x4055
	.sect ".text"
	.global _start
_start:
	call   0x652
