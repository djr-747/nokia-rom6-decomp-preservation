; ROM6 0x8653 MSG_FILL_8653 -- 1w, symbols.yaml program_word.
; Evidence: MVDK fills from DROM-static 0xB373/0xB37B (bytes listed in messages.md) into staged 0x3025/0x119C, CALLD 0x86E3, RET at 0x8674.
; ORIGIN 0x8653
	.sect ".text"
	.global _start
_start:
	call   0x592
