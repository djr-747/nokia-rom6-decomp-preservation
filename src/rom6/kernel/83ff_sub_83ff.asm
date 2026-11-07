; ROM6 0x83FF SUB_83FF -- 20w, symbols.yaml data_word.
; Evidence: Entry 7716 B163 F274 7F55 770E 0000, prev FC00; zero callers; first exit ret @8412 len 20; interior calld 7F55/7F95/7FC6 chain; HYPOTHESIS.
; Wave-12: exit ret @8412 owned here; ret-first twin 8412_sub_83ff.asm deleted (was ret@8412 + dup of 8413 head).
; ORIGIN 0x83FF
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @83FF 7716 stm    #-20125,ar6
	stm    #-20125,ar6
	; @8401 f274 calld  0x7f55
	calld  0x7f55
	; @8403 770e stm    #0,t
	stm    #0,t
	; @8405 7716 stm    #-20100,ar6
	stm    #-20100,ar6
	; @8407 f274 calld  0x7f95
	calld  0x7f95
	; @8409 770e stm    #-12,t
	stm    #-12,t
	; @840B f274 calld  0x7fc6
	calld  0x7fc6
	; @840D 7712 stm    #10884,ar2
	stm    #10884,ar2
	; @840F 69f8 orm    #1536,*(0x2a87)
	orm    #1536,*(0x2a87)
	; @8412 fc00 ret
	ret
