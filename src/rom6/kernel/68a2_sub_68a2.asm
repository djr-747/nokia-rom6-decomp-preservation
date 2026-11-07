; ROM6 0x68A2 SUB_68A2 -- 21w, symbols.yaml data_word.
; Evidence: Bound 68A2-68B6 (21w, exit FE00@68B4 + delays 68B5/68B6); callers F074 @64A9/66E8 (both slice- verified call 0x68a2); HYPOTHESIS.
; ORIGIN 0x68A2
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x51e),#2048
	ld     *(0x2fd9),b
	xc     2,ntc
	ld     *(0x91b),b
	neg    b
	add    #159,b
	nop
	nop
	xc     2,blt
	add    #204,b
	rc     tc
	sub    *ar6,b
	retd
	ld     #0,a
	max    b
