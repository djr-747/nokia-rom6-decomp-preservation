; ROM6 0x9F35 MSG_STAGE_9F35 -- 1w, symbols.yaml program_word.
; Evidence: Copy 0x093A to 0x1000 (BRC 119) via engine 0x9F19, RET at 0x9F41. Variant of 0x9F28 (AR2 0x1100 vs 0x1000, BRC 139 vs 119); callers F074 9F35 at 0x9CB2/0x9CBA/0xB527/0xB52B, plus c
; Pool: single-word PSHM AR2 (stack push, no C form -- unmodelable addressing state); stays .asm, bytes verified.
; Wave-13: body annexed (gap orphan; 1w head + 12w body now whole routine, still pool: pshm entry unmodelable).
; ORIGIN 0x9F35
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar2
	pshm   ar3
	stm    #4096,ar2
	stm    #2362,ar3
	calld  0x9f19
	stm    #119,brc
	popm   ar3
	popm   ar2
	ret
