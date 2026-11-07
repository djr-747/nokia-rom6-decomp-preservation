; ROM6 0x3199 WORKER_3199 -- 205w, symbols.yaml data_word.
; Evidence: Entry 61F8 051D (bitf *(0x51d)#256), post-ret (FC00@3198); bound 3199-3265 (205w, exit F073@3264->2E64); interior joins incl parent-verified F073 31E9->31EE, 3219->321E, 3235->325D
; Wave-13: exit ret @3266 owned here (gap orphan annexed).
; ORIGIN 0x3199
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x51d),#256
	rc     tc
	andm   #-361,*(0x537)
	bitf   *(0x3ec8),#16
	bc     0x31bc,ntc
	ld     *ar2+0%,a
	and    #3871,a
	ld     a,-4,b
	and    #240,b
	stlm   b,ar1
	and    #31,a
	stl    a,*(0x58b)
	ld     b,a
	sub    #80,b
	bc     0x31ba,beq
	ld     a,b
	sub    #48,b
	bc     0x31bb,bneq
	ld     #128,a
	xc     1,ntc
	ldm    ar1,a
	stm    #9787,ar4
	and    #240,a
	andm   #-241,*ar4
	or     *ar4,a
	stl    a,*ar4
	bitf   *(0x11),#64
	ld     #124,a
	orm    #32,*(0x54f)
	xc     2,tc
	ld     #299,a
	bc     0x31d8,tc
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     1,tc
	ld     #174,a
	bitf   *(0x11),#32
	andm   #-16,*(0x51f)
	xc     2,tc
	ld     #374,a
	bitf   *(0x3ec8),#16
	bc     0x31eb,ntc
	cmpm   *(0x11),#48
	b      0x31ee
	bitf   *(0x11),#128
	stm    #1292,ar3
	ld     *(0x3ec8),b
	and    #64,b
	st     #1,*ar3
	xc     2,bgt
	st     #0,*ar3
	bc     0x3200,ntc
	ld     #498,a
	xc     2,bgt
	ld     #548,a
	bitf   *(0x3ec8),#4096
	bc     0x320c,ntc
	cmpm   *(0x11),#80
	bc     0x320c,ntc
	ld     #473,a
	bitf   *(0x3ec8),#16
	bc     0x321b,ntc
	cmpm   *(0x11),#64
	bc     0x321e,tc
	cmpm   *(0x11),#32
	b      0x321e
	bitf   *(0x11),#96
	bc     0x3223,ntc
	st     #512,*(0x50c)
	stl    a,*(0x50d)
	st     #0,*(0x50e)
	call   0x5b6
	bitf   *(0x58f),#15
	bc     0x3237,ntc
	andm   #-33,*(0x54f)
	orm    #2,*(0x2453)
	b      0x325d
	bitf   *(0x3ec8),#64
	nop
	nop
	stm    #11,ar4
	xc     2,tc
	stm    #7,ar4
	stm    #3561,ar3
	st     #32767,*ar3+
	rptz   a,#82
	stl    a,*ar3+
	xc     2,tc
	rpt    #53
	stl    a,*ar3+
	banz   0x3245,*ar4-
	stm    #1359,ar3
	stm    #1310,ar4
	bitf   *ar3,#8
	andm   #-16385,*ar4
	xc     2,tc
	orm    #16384,*ar4
	andm   #-9,*ar3
	andm   #-9,*(0x51e)
	bitf   *(0x3ec8),#16
	bc     0x3266,ntc
	call   0x2e2f
	b      0x2e64
	ret
