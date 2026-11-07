; ROM6 0x4EF3 FRAG_4EF3 -- 71w, symbols.yaml data_word.
; Evidence: Bound 4EF3-4F39 (71w; exit RET FC00@4F39 byte-verified, exit scan clean); entry BD F273@4EEF-> 4EF9 byte-verified (delayed branch from existing 4EE0 span into head+6 — valid span e
; ORIGIN 0x4EF3
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9302,ar3
	stm    #9750,ar4
	ld     *(0x2618),b
	or     *ar4,a
	stl    a,*ar2+
	ld     *(0x2f20),8,a
	or     *ar3+,a
	cmpm   *(0x250f),#34
	bc     0x4f0e,ntc
	cmpm   *(0x2f1f),#112
	bc     0x4f11,tc
	cmpm   *(0x2f1f),#176
	bc     0x4f11,tc
	stl    a,*ar2+
	b      0x4f1d
	pshm   bl
	pshm   bh
	pshm   bg
	ld     *(0x3490),b
	and    #7,b
	or     b,9,a
	stl    a,*ar2+
	popm   bg
	popm   bh
	popm   bl
	bitf   *(0x3eb5),#512
	bc     0x4f2c,ntc
	bitf   *(0x586),#1
	bc     0x4f2c,ntc
	mvdd   *ar3,*ar2
	addm   #2,*ar2+
	b      0x4f2d
	mvdd   *ar3,*ar2+
	stl    b,*ar2+
	mvkd   0x2615,*ar2+
	rptbd  0x4f38
	stm    #12160,ar4
	ldu    *ar4+,a
	sftl   a,-8,b
	sftl   a,8
	or     a,b
	stl    b,*ar2+
	ret
