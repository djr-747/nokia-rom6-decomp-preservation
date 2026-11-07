; ROM6 0x9331 SUB_9331 -- 91w, symbols.yaml data_word.
; Evidence: Bound 9331-938B (91w; exit RET FC00@938B byte-verified); entry F074 0676 (objdump call); caller F074@0x930D byte-verified; interior cipher loop F272@9345->936B + F072@936E->9389; C
; ORIGIN 0x9331
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x676
	rsbx   st1,cpl
	ld     #0,dp
	stm    #-19451,ar4
	ld     #0,a
	stlm   a,ar0
	stm    #6,ar5
	mvdm   0x60,ar3
	st     #8,0x60
	mar    *+ar6(0xfffc)
	mar    *+ar1(0xffe0)
	stm    #24,brc
	rptbd  0x936b
	stm    #13407,ar2
	ld     *ar4+0,t
	and    #24,a,b
	sfta   b,-3
	stlm   b,ar0
	and    #31,a,b
	mar    *ar6+0
	bitt   *ar6-0
	stlm   b,ar0
	roltc  a
	mar    *+ar6(0xfffc)
	bitf   0x08,#64
	mar    *ar1+0
	ld     *ar1-0,16,b
	xc     1,tc
	sfta   b,8
	and    #-256,16,b
	sfta   b,8
	sfta   b,-13
	abs    b
	sth    b,*ar2-
	bitf   0x08,#32
	and    #7,a,b
	xc     1,tc
	add    0x60,b
	stlm   b,ar0
	mar    *+ar1(0xffe0)
	mar    *ar4-0
	stm    #72,brc
	rptb   0x9389
	ld     *ar4+0,t
	and    #24,a,b
	sfta   b,-3
	stlm   b,ar0
	nop
	nop
	mar    *ar6+0
	bitt   *ar6-0
	roltc  a
	mar    *+ar6(0xfffc)
	bitf   0x08,#32
	and    #7,a,b
	xc     1,tc
	add    0x60,b
	stlm   b,ar0
	banz   0x9389,*ar5-
	sth    a,*ar3-
	stl    a,*ar3-
	stm    #31,ar5
	mar    *ar4-0
	ssbx   st1,cpl
	ret
