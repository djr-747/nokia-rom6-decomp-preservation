; ROM6 0x84AF SUB_84AF -- 32w, symbols.yaml data_word.
; Evidence: Entry F074 05A0 69F8 0029 0004 7758, prev FC00; zero callers; first exit ret @84CE len 32; interior call 05A0 + bc pair 84B9->84B6/84C7->84C4 cond; HYPOTHESIS.
; Wave-12: exit ret @84CE owned here; ret-first twin 84ce_sub_84af.asm deleted (was ret@84CE + dup of 84CF head 84CF-84EE).
; ORIGIN 0x84AF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a0
	orm    #4,*(0x29)
	stm    #-3,clkmd
	bitf   *(0x58),#1
	bc     0x84b6,tc
	stm    #0,clkmd
	nop
	portw  *(0x15),0
	idle   3
	stm    #20974,clkmd
	bitf   *(0x58),#1
	bc     0x84c4,ntc
	andm   #-5,*(0x29)
	rpt    #3
	nop
	ret
