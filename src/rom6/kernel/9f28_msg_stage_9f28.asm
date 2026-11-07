; ROM6 0x9F28 MSG_STAGE_9F28 -- 1w, symbols.yaml program_word.
; Evidence: Copy 0x093A to 0x1100 (BRC 139) via engine 0x9F19, RET at 0x9F34. Entry words 4A12 4A13 7712 1100 7713 093A F274 9F19 771A 008B; callers F074 at 0xB51A/0xB51E verified.
; Pool: single-word PSHM AR2 (stack push, no C form -- unmodelable addressing state); stays .asm, bytes verified.
; ORIGIN 0x9F28
	.sect ".text"
	.global _start
_start:
	pshm   ar2
