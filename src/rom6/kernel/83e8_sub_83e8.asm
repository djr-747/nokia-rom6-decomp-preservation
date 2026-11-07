; ROM6 0x83E8 SUB_83E8 -- 23w, symbols.yaml data_word.
; Evidence: Entry 7716 B194 F274 7F55 770E FFFF, prev FC00; zero callers; first exit ret @83FE len 23; interior calld 7F55/7F95/7FC6 chain; HYPOTHESIS.
; Wave-12: exit ret @83FE owned here; ret-first twin 83fe_sub_83e8.asm deleted (was ret@83FE + dup of 83FF head + 8413-8414).
; ORIGIN 0x83E8
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-20076,ar6
	calld  0x7f55
	stm    #-1,t
	stm    #-20108,ar6
	calld  0x7f95
	stm    #-13,t
	calld  0x7fc6
	stm    #10884,ar2
	st     #0,*(0x2630)
	orm    #1536,*(0x2a87)
	ret
