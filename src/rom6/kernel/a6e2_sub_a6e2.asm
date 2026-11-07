; ROM6 0xA6E2 SUB_A6E2 -- 106w, symbols.yaml data_word.
; Evidence: Post-RET head F074 065E; interior CALLs 8641/8C0A/867E/9DF4; first exit ret FC00 @A74B; bound A6E2-A74B; 8FFB/E61D FB81 fcalld far-1A6E2 correctly not inbound; HYPOTHESIS.
; ORIGIN 0xA6E2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65e
	cmpm   *(0x2510),#193
	rc     ntc
	bitf   *(0x51c),#3
	bc     0xa732,tc
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	bc     0xa724,aneq
	stm    #1308,ar2
	bitf   *ar2,#16
	bc     0xa71b,ntc
	bitf   *ar2,#512
	bc     0xa71b,ntc
	ld     *(0x1f3),a
	sub    *(0x559),a
	mvdm   0x559,ar3
	xc     2,alt
	add    #632,a
	sub    #187,a
	bc     0xa71b,alt
	stm    #632,bk
	cmpm   *ar3,#-8
	bc     0xa715,ntc
	mar    *ar3+%
	b      0xa70e
	andm   #-769,*ar2
	mvmd   ar3,0x243
	call   0x8641
	st     #12854,*(0x337c)
	st     #12854,*(0x337d)
	ld     #159,a
	call   0xba56
	calld  0xab78
	stm    #12854,ar2
	calld  0x8bde
	stm    #12854,ar4
	call   0x8c0a
	call   0x867e
	b      0xa73a
	orm    #256,*(0x51e)
	stm    #12432,ar4
	rpt    #75
	mvkd   0x2799,*ar4+
	stm    #12432,ar3
	calld  0x86e3
	stm    #9593,ar4
	calld  0x872b
	stm    #9593,ar4
	or     *(0x257e),a
	stl    a,*(0x257e)
	st     #193,*(0x25a0)
	ret
