; ROM6 0x3E53 PORT_SEQ_SWEEP -- 106w, symbols.yaml data_word.
; Evidence: Entry F074 063C; bounds 3E53-3EBC + 3EBE-3EE0 (carve-out: routine executes through existing 0x3EBD FIR table word via portw *(0xc),pa49 in pa48/49/50 triple; table word not counted
; ORIGIN 0x3E53
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x63c
	portr  3,*(0x8)
	and    #-2,a
	nop
	portw  *(0x8),3
	rpt    #22
	nop
	bitf   *(0x7),#2048
	ssbx   st1,intm
	andm   #-8193,*(0x51e)
	bc     0x3e6c,ntc
	orm    #8192,*(0x51e)
	bitf   *(0x3ec8),#32
	call   0x3ee1
	add    *(0x3eb6),a
	sub    *(0x36a),a,b
	bc     0x3e79,blt
	ld     b,a
	nop
	portw  *(0x8),11
	rpt    #20
	nop
	bc     0x3ed2,ntc
	cmpm   *(0x250f),#34
	bc     0x3eb3,ntc
	mvdm   0x2660,ar3
	mvdm   0x265e,ar2
	cmpm   *ar3(0x1),#17408
	bc     0x3eb3,ntc
	sub    *ar2(0x1),a,b
	bc     0x3eb3,blt
	nop
	portw  *ar2+,48
	nop
	nop
	portw  *ar3+,49
	nop
	nop
	portw  *ar3+,50
	nop
	nop
	portw  *(0x8),4
	rpt    #20
	nop
	mvdk   *(0x8),0x58e
	mar    *ar2+
	st     #32,*(0x13d0)
	mvmd   ar2,0x265e
	mvmd   ar3,0x2660
	b      0x3ed2
	or     #256,16,a
	dld    *(0x3ef6),b
	nop
	portw  *(0x9),48
	nop
	nop
