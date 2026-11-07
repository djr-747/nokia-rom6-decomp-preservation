; ROM6 0x97DD WRAP_97DD -- 208w, symbols.yaml data_word.
; Evidence: Entry F074 05CA 7212 21FD 61F8 20FF 0080; callers F074@9530/96FD/9735/9747; first-RET @0x98AC (208w); HYPOTHESIS.
; ORIGIN 0x97DD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ca
	mvdm   0x21fd,ar2
	bitf   *(0x20ff),#128
	bcd    0x97f1,ntc
	stm    #250,bk
	portr  12,*(0x8)
	or     *(0x3eca),a
	nop
	portw  *(0x8),12
	st     #0,*(0x20fb)
	ld     *ar2+%,a
	stlm   a,ar3
	ld     *(0x2201),a
	add    #-19443,a
	stlm   a,ar1
	portr  54,*(0x8)
	ld     *ar1,b
	bacc   b
	ldu    *(0x21ff),b
	subs   *(0x2204),b
	bc     0x980c,blt
	ld     #1,a
	orm    #2048,*(0x20ff)
	b      0x988b
	ld     #0,a
	st     #-1,*(0x2200)
	bd     0x9883
	stm    #21845,ar3
	mar    *ar2-%
	ldm    ar2,b
	sub    *(0x21fc),b
	mar    *ar2+%
	ld     #1,a
	st     #0,*(0x2200)
	bc     0x988b,beq
	mar    *ar2+%
	ld     *ar2,a
	add    #6,a
	stl    a,*(0x2200)
	mar    *ar2-%
	ld     #2,a
	bd     0x9883
	mvmd   ar2,0x21fd
	ld     #2,a
	ld     *(0x2200),b
	sub    #2,b
	mvmd   ar2,0x21fd
	xc     2,bleq
	ld     #1,a
	ld     #0,b
	bd     0x9883
	stl    b,*(0x2200)
	ld     *(0x21fc),a
	sub    *(0x21fd),a
	bitf   *(0x20ff),#4096
	xc     2,alt
	add    #250,a
	ld     #1,b
	sfta   a,1
	xc     1,tc
	add    b,a
	bitf   *(0x20ff),#8192
	nop
	nop
	xc     1,tc
	sub    b,a
	nop
	nop
	xc     2,alt
	add    #250,1,a
	sub    a,b
	bcd    0x9866,beq
	stl    a,*(0x2200)
	bc     0x9873,aeq
	bcd    0x9861,ntc
	ldm    ar3,a
	sftl   a,8
	ldu    *ar2,b
	or     b,-8,a
	stlm   a,ar3
	ld     #5,a
	bd     0x9883
	mvmd   ar2,0x21fd
	bcd    0x986d,ntc
	ldm    ar3,a
	sftl   a,8
	mvmd   ar2,0x21fd
	stlm   a,ar3
	xorm   #8192,*(0x20ff)
	ld     #4,a
	b      0x9883
	ld     #3,a
	b      0x988b
	or     #256,a
	nop
	nop
	xc     2,aeq
	and    #-257,a
	nop
	portw  *(0x8),54
	b      0x9839
	ldm    ar3,b
	nop
	portw  *(0xb),52
	retd
	stl    a,*(0x2201)
	stl    a,*(0x2201)
	portr  2,*(0x8)
	or     #256,a
	nop
	portw  *(0x8),2
	bitf   *(0x20ff),#2
	bc     0x98ac,ntc
	stm    #96,ar2
	portr  54,*ar2
	andm   #-2,*ar2
	nop
	portw  *ar2,54
	nop
	portr  2,*ar2
	andm   #-513,*ar2
	nop
	portw  *ar2,2
	ret
