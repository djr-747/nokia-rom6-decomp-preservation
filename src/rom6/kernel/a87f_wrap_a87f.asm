; ROM6 0xA87F WRAP_A87F -- 28w, symbols.yaml data_word.
; Evidence: Entry F074 067C 69F8 051E 0100 7712; bound A87F-A89A (FC00@A89A); callers F074 @B030/B09D/B0E4 (objdump-verified, outside-gap audio region); interior call 067C; cond bc A8B1/A89B/A
; ORIGIN 0xA87F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67c
	orm    #256,*(0x51e)
	stm    #9593,ar2
	rpt    #8
	mvkd   0x9c8,*ar2+
	ld     *(0x51f),a
	and    #6144,a
	bc     0xa8b1,aeq
	cmpm   *(0x8),#2048
	bc     0xa89b,ntc
	ld     *(0x3082),a
	or     *(0x2ef7),a
	bc     0xa8b9,aneq
	ret
