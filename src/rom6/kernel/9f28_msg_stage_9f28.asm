; ROM6 0x9F28 MSG_STAGE_9F28 -- 1w, symbols.yaml program_word.
; Evidence: Copy 0x093A to 0x1100 (BRC 139) via engine 0x9F19, RET at 0x9F34. Entry words 4A12 4A13 7712 1100 7713 093A F274 9F19 771A 008B; callers F074 at 0xB51A/0xB51E verified.
; Pool: single-word PSHM AR2 (stack push, no C form -- unmodelable addressing state); stays .asm, bytes verified.
; Wave-13: body annexed (gap orphan; 1w head + 12w body now whole routine, still pool: pshm entry unmodelable).
; ORIGIN 0x9F28
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar2
	pshm   ar3
	stm    #4352,ar2
	stm    #2362,ar3
	calld  0x9f19
	stm    #139,brc
	popm   ar3
	popm   ar2
	ret
