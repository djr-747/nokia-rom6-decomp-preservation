; ROM6 0x39F0 PA60_57_WRITER_A -- 54w, symbols.yaml data_word.
; Evidence: Entry F074 0630; bound 39F0-3A25 (retd@3A23 +2 verified); caller F074@2BCD; portw pa60@3A0C/3A11/3A1F + portr pa57 + portw pa0@3A03 + call 3ADE@39F7; HYPOTHESIS.
; ORIGIN 0x39F0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x630
	cmpm   *(0x250f),#34
	bc     0x39f9,tc
	call   0x3ade
	bitf   *(0x7),#2048
	ssbx   st1,intm
	portr  0,*(0x8)
	and    #-97,a
	nop
	portw  *(0x8),0
	rpt    #20
	nop
	xc     1,ntc
	rsbx   st1,intm
	ld     #3,a
	nop
	portw  *(0x8),60
	ld     #7,a
	nop
	portw  *(0x8),60
	stm    #13,brc
	rptb   0x3a1a
	portr  57,*ar2+
	nop
	portr  57,*ar2
	ld     #2,a
	nop
	portw  *(0x8),60
	ld     *ar2,a
	retd
	sfta   a,-12
	stl    a,*ar2
