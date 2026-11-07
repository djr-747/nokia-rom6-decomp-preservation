; ROM6 0x4007 PORT0_TXN -- 1w, symbols.yaml program_word.
; Evidence: Port-0 transaction in two pa0-strobe phases (OR 12, RPT-22 wait), each gated on *(0x3EB5) bit 1. Phase one: SUB #7 check, PORTW pa40, CALL 0x40A1 worker, pa45 poll (AND #4096), POR
; ORIGIN 0x4007
	.sect ".text"
	.global _start
_start:
	call   0x652
