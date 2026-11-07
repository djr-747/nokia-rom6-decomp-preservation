; ROM6 0x38C9 ROUTINE_38C9 -- 45w, symbols.yaml data_word.
; Evidence: Bound 38C9-38F5 (87w; exit RET FC00@38F5 byte-verified, exit scan clean); entries cc F930@38B3-> 38C9 byte-verified (cond call, from FRAG_389C interior) + post-RET head (FC00@38C8)
; ORIGIN 0x38C9
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x3ec8),#128
	ldm    ar3,b
	bc     0x38d6,tc
	bitf   *(0x3ec8),#32
	nop
	nop
	xc     1,tc
	sfta   a,1
	bitf   *(0x51f),#128
	bc     0x38de,ntc
	bc     0x38de,beq
	sfta   a,1
	bitf   *(0x3ec8),#32
	sub    #38,a
	sfta   a,-6,b
	stl    b,*(0x60)
	sftl   b,6
	subs   *(0xb),a
	ld     *(0x60),b
	sfta   b,7
	or     a,b
	add    #38,b
	bc     0x38f6,ntc
	orm    #17408,*(0xc)
	ld     b,a
	ret
