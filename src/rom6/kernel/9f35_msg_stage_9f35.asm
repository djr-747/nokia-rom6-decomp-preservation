; ROM6 0x9F35 MSG_STAGE_9F35 -- 1w, symbols.yaml program_word.
; Evidence: Copy 0x093A to 0x1000 (BRC 119) via engine 0x9F19, RET at 0x9F41. Variant of 0x9F28 (AR2 0x1100 vs 0x1000, BRC 139 vs 119); callers F074 9F35 at 0x9CB2/0x9CBA/0xB527/0xB52B, plus c
; Pool: single-word PSHM AR2 (stack push, no C form -- unmodelable addressing state); stays .asm, bytes verified.
; ORIGIN 0x9F35
	.sect ".text"
	.global _start
_start:
	pshm   ar2
