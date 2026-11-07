; ROM6 0x303F FRAG_303F -- 214w, symbols.yaml data_word.
; Evidence: Bound 303F-3114 (exit F073@3113->2E64 + operand 3114; CORRECTED from team 311E: FC00@311E is WORKER_311F boundary ret, not in-span); post-branch head (POST_RETD_3028 ends 303E); ze
; ORIGIN 0x303F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+%,a
	sftl   a,-4,b
	stlm   a,ar7
	ld     *(0x51f),a
	and    #240,b
	and    #-241,a
	or     a,b
	stl    b,*(0x51f)
	ldm    ar7,a
	and    #12288,a,b
	sub    #4096,b
	stm    #852,ar4
	xc     2,beq
	stm    #1200,ar4
	sub    #4096,b
	nop
	nop
	xc     2,beq
	stm    #1200,ar4
	xc     2,bgt
	stm    #1200,ar4
	rpt    #17
	mvdd   *ar2+0%,*ar4+
	ld     *ar2+%,a
	ldm    ar7,b
	and    #12288,b
	sub    #4096,b
	stm    #1411,ar4
	xc     2,beq
	stm    #1412,ar4
	sub    #4096,b
	nop
	nop
	xc     2,beq
	stm    #1412,ar4
	xc     2,bgt
	stm    #1412,ar4
	stl    a,*ar4
	ldm    ar7,b
	and    #4096,b
	stm    #870,ar4
	rpt    #1
	mvdd   *ar2+0%,*ar4+
	ld     *ar2+%,a
	stl    a,*(0x569)
	stm    #1140,ar4
	xc     2,bneq
	stm    #1180,ar4
	bitf   *(0x3ec8),#32
	bc     0x3097,ntc
	rpt    #8
	mvdd   *ar2+0%,*ar4+
	stm    #11,brc
	stm    #4736,ar4
	rptb   0x3094
	mvdd   *ar2+0%,*ar4+
	mar    *ar4+
	b      0x3099
	rpt    #19
	mvdd   *ar2+0%,*ar4+
	ldm    ar7,b
	and    #12288,b
	sub    #4096,b
	stm    #820,ar4
	xc     2,beq
	stm    #1049,ar4
	sub    #4096,b
	nop
	nop
	xc     2,beq
	stm    #1049,ar4
	xc     2,bgt
	stm    #1049,ar4
	ldm    ar7,b
	and    #4096,b
	rpt    #31
	mvdd   *ar2+0%,*ar4+
	ldu    *ar2+%,a
	stm    #1409,ar4
	xc     2,bneq
	stm    #1410,ar4
	stl    a,*ar4
	bc     0x30be,beq
	ld     *ar2+%,a
	stl    a,*(0x57a)
	bitf   *(0x51f),#128
	bc     0x30c5,ntc
	bc     0x30c9,bneq
	ldu    *ar4,a
	ld     #12,b
	call   0x4007
	ldm    ar7,a
	and    #255,a
	bc     0x310f,aeq
	sub    #255,a
	bc     0x30e6,aneq
	andm   #-193,*(0x0)
	stm    #-16372,spc1
	ssbx   st1,intm
	portr  0,*(0x8)
	or     #16,a
	nop
	portw  *(0x8),0
	rpt    #16
	nop
	rsbx   st1,intm
	b      0x310f
	andm   #-193,*(0x0)
	stm    #-16376,spc1
	stm    #-16184,spc1
	bitf   *(0x577),#64
	bc     0x30f8,ntc
	stm    #-16372,spc0
	stm    #-16180,spc0
	b      0x30fc
	stm    #-16376,spc0
	stm    #-16184,spc0
	ssbx   st1,intm
	portr  0,*(0x8)
	and    #-17,a
	nop
	portw  *(0x8),0
	rpt    #12
	nop
	rsbx   st1,intm
	andm   #-3073,*(0x51c)
	orm    #1024,*(0x51c)
	mvdk   *ar2+0%,0x585
	call   0x2e2f
	b      0x2e64
