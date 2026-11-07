; ROM6 0x2C88 RING_REPORT_GATE -- 2w, symbols.yaml program_word.
; Evidence: Ring-space check on 0x8E4/0x8E5, combines AR4/AR5 into header word stored to ring, CALL 0x93CE, RET. Block20 invokes with 0x74/0x36 (SIML validation report).
; 2-word head (call 0x622 RAM-resident); falls into 2C8A ring-arith span (abuts, owned by 2c8a_ring_arith_2c8a.asm). Recombine-clean.
; ORIGIN 0x2C88
	.sect ".text"
	.global _start
_start:
	call   0x622
