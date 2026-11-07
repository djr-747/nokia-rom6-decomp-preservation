; ROM6 0x867E SUB_867E -- 81w, symbols.yaml data_word.
; Evidence: Bound 867E-86CE (81w; exit FC00@86CE); entry ext CALL F074@A72E->867E (bytes F074 867E F073 A73A lane); head F074 0592; interior calls CALL 86CF@86A2/86B6, CALLD 87EB@86B8, CALL 87
; ORIGIN 0x867E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x592
	ssbx   st1,ovm
	orm    #256,*(0x51e)
	bitf   *(0x51e),#4096
	bc     0x86cd,ntc
	ld     *(0x2f03),a
	bc     0x86c1,agt
	ld     *(0x10ff),b
	sub    #4,b,a
	bc     0x86ae,ageq
	stm    #4350,ar4
	ld     *ar4,a
	sub    b,a
	sub    #23,a,b
	bcd    0x86a2,blt
	addm   #1,*ar4
	orm    #256,*(0x51e)
	b      0x86a4
	call   0x86cf
	stm    #4351,ar2
	addm   #1,*ar2
	ld     #4,b
	sub    *ar2,b
	bc     0x86cd,bneq
	b      0x86b8
	st     #0,*(0x10fe)
	stm    #4520,ar3
	rpt    #8
	mvkd   0x11b1,*ar3+
	call   0x86cf
	calld  0x87eb
	stm    #4529,ar2
	call   0x87d3
	stl    a,*ar2
	b      0x86cd
	ld     #1,a
	sth    a,*(0x10ff)
	orm    #256,*(0x51e)
	stm    #4350,ar2
	add    *ar2,a
	ld     #32,b
	min    a
	stl    a,*ar2
	rsbx   st1,ovm
	ret
