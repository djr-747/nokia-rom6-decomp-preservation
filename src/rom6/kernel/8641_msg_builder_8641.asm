; ROM6 0x8641 MSG_BUILDER_8641 -- 1w, symbols.yaml program_word.
; Evidence: Sub-call chain to 0x8675, RET at 0x864D. Called from dispatcher switch, mask 0xA7xx, COBBA_WORKER.
; ORIGIN 0x8641
	.sect ".text"
	.global _start
_start:
	call   0x592
