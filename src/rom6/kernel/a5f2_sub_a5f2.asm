; ROM6 0xA5F2 SUB_A5F2 -- 35w, symbols.yaml data_word.
; Evidence: Entry 61F8 3EB5 0040; bound A5F2-A614 ret; interior bc A60A @A5F5 + bc A606 @A600 + calld ABD2 @A610; inbound call @292E + post-RET A5F1; HYPOTHESIS.
; ORIGIN 0xA5F2
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x3eb5),#64
	bc     0xa60a,ntc
	ldu    *(0x3ebc),a
	and    #32767,a
	sub    *(0x2636),a
	portr  12,*(0xb)
	bc     0xa606,agt
	ld     *(0x3ecb),a
	cmpl   a
	and    a,b
	nop
	portw  *(0xb),12
	bitf   *(0x2628),#512
	rc     ntc
	stm    #9747,ar2
	calld  0xabd2
	stm    #555,ar3
	ret
