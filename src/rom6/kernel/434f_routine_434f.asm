; ROM6 0x434F ROUTINE_434F -- 29w, symbols.yaml data_word.
; Evidence: Bound 434F-436B (30w; exit RET FC00@436B byte-verified; 1w orphan 434E (7FFF) stays dark); entries call@344D (F074) + calld@526D/71F4 (F274) ->434F head+1 byte-verified (split-head
; ORIGIN 0x434F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x608
	pshm   ar7
	stm    #7,ar7
	ld     #0,b
	bitf   *(0x3ec8),#64
	nop
	nop
	stlm   b,t
	stlm   b,ar0
	xc     2,tc
	stm    #11,ar7
	xc     2,tc
	stm    #960,ar0
	call   0x436c
	stm    #23,ar7
	calld  0x436c
	stm    #511,ar0
	popm   ar7
	ret
