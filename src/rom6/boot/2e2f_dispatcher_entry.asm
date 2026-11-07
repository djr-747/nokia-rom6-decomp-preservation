; ROM6 0x2E2F DISPATCHER_ENTRY -- 10w, symbols.yaml program_word.
; Evidence: Multi-clause shared dispatcher. Flag-gated CALLs 0x05A0, 0x2C88, 0x2E64, 0x37D8, 0x942E, 0x2D8F; opcode match on *(0x54D); port I/O under INTM lock. Tail closed: opcode-range check
; ORIGIN 0x2E2F
	.sect ".text"
	.global _start
_start:
	call   0x5a0
	bitf   *(0x54d),#4
	rc     tc
	mvkd   0x54c,*(0x853)
	ret
