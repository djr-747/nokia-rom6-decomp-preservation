; ROM6 0xC4E8 COPY_ABSMAX_C4E8 -- 85w, symbols.yaml data_word.
; Evidence: Entry MVMD 0x3148/49; bounds C4E8-C53C + C53D-C555 (called from C47A); callers BD15/BD20 calld; RPTBD TMPYR + BRC 87 ABS/MAX + RPT #87 ST||ADD; HYPOTHESIS.
; ORIGIN 0xC4E8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6dc
	mvmd   ar1,0x3148
	mvmd   ar2,0x3149
	stm    #7,brc
	stm    #10420,ar2
	mvmm   ar1,ar5
	rptbd  0xc4f9
	stm    #-17221,ar3
	ld     *ar2+,t
	mpyr   *ar3+,a
	sth    a,*ar5+
	mvdm   0x3149,ar3
	rpt    #71
	mvdd   *ar3+,*ar5+
	mvdm   0x3149,ar4
	stm    #7,brc
	stm    #-17214,ar2
	rptbd  0xc50a
	mar    *+ar4(0x48)
	ld     *ar2-,t
	mpyr   *ar4+,a
	sth    a,*ar5+
	rptz   a,#39
	stl    a,*ar5+
	mvdm   0x3149,ar3
	stm    #10420,ar2
	mar    *+ar3(0x48)
	rpt    #7
	mvdd   *ar3+,*ar2+
	stm    #87,brc
	ssbx   st1,ovm
	mvdm   0x3148,ar2
	st     #15,0x44
	rptbd  0xc523
	ld     *ar2+,16,a
	abs    a
	ld     *ar2+,16,b
	abs    b
	max    a
	rsbx   st1,ovm
	sfta   a,-16
	exp    a
	bcd    0xc53b,aeq
	mvdm   0x3148,ar2
	ldm    t,a
	mvmm   ar2,ar3
	add    #-16,a
	bcd    0xc537,agt
	stl    a,0x44
	xor    b
	neg    a
	stlm   a,t
	ldu    0x42,b
	norm   b
	add    *ar2+,16,b,a
	ld     0x44,asm
	rpt    #87
	st     a,*ar3+ || add    *ar2+,a
	ld     #0,asm
	ret
