; ROM6 0x9D2D WRAP_9D2D -- 109w, symbols.yaml data_word.
; Evidence: Entry F074 06BC 10F8 057C 7719 00C8; callers F074@9E1F F274@9E4F/9E6D/9EB1; first-RET @0x9D99 (109w); HYPOTHESIS.
; ORIGIN 0x9D2D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6bc
	ld     *(0x57c),a
	stm    #200,bk
	stm    #1,ar0
	and    #4095,a
	mar    *ar2+%
	stm    #2140,ar4
	bitf   *(0x860),#2
	bc     0x9d60,ntc
	xc     2,aleq
	mar    *+ar2(0xffaf)%
	stm    #79,brc
	rptb   0x9d5d
	ld     *ar2,-8,a
	stlm   a,ar5
	nop
	nop
	mar    *+ar5(0xb495)
	mpy    *ar4,*ar5,a
	xc     1,bneq
	add    *ar3,16,a
	sth    a,*ar3+
	ld     *ar2+%,a
	stlm   a,ag
	sfta   a,-16
	sfta   a,-16
	stlm   a,ar5
	nop
	nop
	mar    *+ar5(0xb495)
	mpy    *ar4,*ar5,a
	xc     1,bneq
	add    *ar3,16,a
	sth    a,*ar3+
	b      0x9d99
	call   0x6c0
	bitf   *(0x860),#144
	bc     0x9d8c,ntc
	xc     2,aleq
	mar    *+ar2(0xffee)%
	stm    #2504,ar4
	rpt    #16
	mvdd   *ar2+0%,*ar4+
	stm    #2504,ar4
	pshm   ar2
	rsbx   st1,ovm
	calld  0x86fb
	stm    #12432,ar3
	ssbx   st1,ovm
	call   0x9f28
	calld  0x8a54
	stm    #13014,ar2
	call   0x9f28
	stm    #13014,ar3
	stm    #159,brc
	rptbd  0x9d88
	stm    #2140,ar4
	mpy    *ar4,*ar3,a
	sth    a,*ar3+
	popm   ar2
	b      0x9d99
	xc     2,aleq
	mar    *+ar2(0xff5f)%
	stm    #159,brc
	rptbd  0x9d98
	stm    #2140,ar4
	mpy    *ar2+0%,*ar4,a
	xc     1,bneq
	add    *ar3,16,a
	sth    a,*ar3+
	ret
