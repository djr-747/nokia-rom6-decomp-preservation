; ROM6 0x3986 CMD_DISPATCH_PORT15 -- 1w, symbols.yaml program_word.
; Evidence: INTM-gated pa15 strobe (CALL 0x62E head, 0x263A clear, 0x2639 bit-9 check, PORTW pa15, RPT-6 wait, IDLE 1, 0x263A bit-1 check), RET at 0x399D.
; ORIGIN 0x3986
	.sect ".text"
	.global _start
_start:
	call   0x62e
