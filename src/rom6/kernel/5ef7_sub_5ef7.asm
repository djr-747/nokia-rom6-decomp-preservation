; ROM6 0x5EF7 SUB_5EF7 -- 84w, symbols.yaml data_word.
; Evidence: Entry F074 0598; fall-through first exit retd FE00 @5F48 via F273 bd @5F0D entry-linear; bound 5EF7-5F4A; caller F074 @5D87 verified; 937w to 629F crosses exits + existing 613F so 
; ORIGIN 0x5EF7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	stm    #9769,ar2
	ld     #240,a
	and    *(0x250f),a
	cmpm   *(0x8),#32
	bc     0x5f1d,ntc
	ld     *(0x914),a
	sub    *(0x2652),a
	bc     0x5f11,aneq
	bitf   *ar2,#-32752
	bc     0x5f1a,ntc
	bd     0x5f48
	ld     #-3,a
	add    #1,a
	bc     0x5f1a,aneq
	bitf   *ar2,#8320
	ld     #-1,a
	xc     1,ntc
	ld     #0,a
	b      0x5f48
	bitf   *ar2,#16432
	bcd    0x5f48,tc
	ld     #-2,a
	bitf   *ar2,#8320
	bcd    0x5f48,tc
	ld     #-1,a
	bitf   *ar2,#4096
	bc     0x5f1a,ntc
	ld     *(0x565),b
	sub    *(0x915),b
	bc     0x5f1a,beq
	ld     *(0x36d),b
	sub    *(0x250d),b
	bcd    0x5f48,bgeq
	ld     #-3,a
	cmpm   *(0x915),#11
	bc     0x5f1a,tc
	add    #5,b
	bc     0x5f48,bleq
	bd     0x5f48
	ld     #-5,a
	retd
	stl    a,*(0x2661)
