; ROM6 0x5503 MSG_PRODUCER_CONVERGE -- 174w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x5503
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9546,ar2
	stm    #9491,ar3
	rpt    #7
	mvdd   *ar2+,*ar3+
	bitf   *(0x54f),#16
	bc     0x551c,ntc
	mvdk   *(0x2576),0x253f
	cmpm   *(0x250f),#34
	bc     0x5519,ntc
	mvdk   *(0x34cb),0x34ca
	andm   #-17,*(0x54f)
	bitf   *(0x54f),#512
	bc     0x5529,ntc
	stm    #9591,ar2
	stm    #9536,ar3
	mvdd   *ar2,*ar3
	andm   #-513,*(0x54f)
	stm    #9554,ar2
	stm    #9499,ar3
	rpt    #31
	mvdd   *ar2+,*ar3+
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	rpt    #3
	mvdd   *ar2+,*ar3+
	ld     *(0x56d),a
	portr  56,*(0xb)
	or     #16,b
	bc     0x5542,aneq
	and    #-17,b
	nop
	portw  *(0xb),56
	andm   #24944,*(0x2627)
	andm   #-133,*(0x2512)
	ld     *(0x2477),a
	call   0x56de
	call   0x56fc
	stm    #9767,ar1
	ld     *ar1,b
	and    #-16385,b
	cmpm   *(0x2476),#3
	bc     0x5561,ntc
	andm   #-5,*(0x54f)
	or     #16384,b
	stl    b,*ar1
	ld     *(0x250f),a
	and    #240,a,b
	sub    #32,b,a
	st     #-23991,*(0x573)
	bc     0x55ef,aneq
	call   0x6e6
	cmpm   *(0x250f),#47
	bc     0x5577,ntc
	st     #-20649,*(0x573)
	ld     *(0x250f),a
	and    #254,a
	cmpm   *(0x8),#32
	bc     0x5583,ntc
	st     #-20565,*(0x573)
	cmpm   *(0x250f),#34
	bc     0x558b,ntc
	st     #-20116,*(0x573)
	cmpm   *(0x2547),#195
	bc     0x5596,ntc
	st     #-20196,*(0x573)
	st     #193,*(0x2510)
	st     #176,*(0x56f)
	orm    #128,*(0x2512)
	stm    #9485,ar1
	cmpm   *(0x250f),#34
	bc     0x55b1,ntc
	st     #25,*(0x2652)
	st     #12,*(0x2653)
	st     #0,*(0x2651)
	st     #12,*(0x2640)
	b      0x5683
