; ROM6 0x33E8 BIT_LADDER_33E8 -- 115w, symbols.yaml program_word.
; Evidence: Fall-through from 33d8 frag (prev span); bitf/xc B-select ladder, andm mask lanes, ld/or/stl merge, rpt/mvdd sample move with xc-gated second fill, mvmm/mar pointer dance, dark 434F call, dispatcher call/b tails; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x33E8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+0%,a
	stm    #1311,ar3
	bitf   *(0x8),#2
	andm   #-17424,*ar3
	xc     2,tc
	orm    #1024,*ar3
	bitf   *(0x8),#4
	bc     0x33fa,ntc
	orm    #16384,*ar3
	stm    #9787,ar4
	and    #240,a,b
	andm   #-241,*ar4
	or     *ar4,b
	stl    b,*ar4
	bitf   *ar4,#64
	nop
	ld     #124,b
	xc     2,tc
	ld     #299,b
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     1,tc
	ld     #174,b
	bitf   *ar4,#32
	stm    #1309,ar3
	xc     2,tc
	ld     #374,b
	bitf   *ar4,#128
	nop
	nop
	xc     2,tc
	ld     #498,b
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	ld     #548,b
	stl    b,*(0x2a84)
	bitf   *(0x8),#1
	andm   #-9,*ar3
	xc     2,ntc
	orm    #8,*ar3
	ld     *ar2,-8,a
	stl    a,*(0x2bfd)
	ld     *ar2+0%,a
	and    #255,a
	stm    #12032,ar4
	stl    a,*ar4+
	ld     *(0x3ec8),a
	and    #64,a
	rpt    #30
	mvdd   *ar2+0%,*ar4+
	xc     2,agt
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	bc     0x3454,tc
	mvmm   ar2,ar6
	stm    #12063,ar2
	xc     2,agt
	mar    *+ar2(0x4)
	stm    #10886,ar3
	call   0x434f
	stl    b,*(0x2a84)
	st     #32767,*ar3
	mvmm   ar6,ar2
	call   0x2e2f
	orm    #1,*(0x54f)
	b      0x2e64
