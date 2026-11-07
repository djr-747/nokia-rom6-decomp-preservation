; ROM6 0x3A26 PA60_57_WRITER_B -- 91w, symbols.yaml data_word.
; Evidence: Entry E800 F074 0632; bound 3A26-3A80; caller F274@4D13 (+own F274@8081 at interior entry 3A27); portr pa56 + portw pa60/pa57; HYPOTHESIS.
; ORIGIN 0x3A26
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	call   0x632
	cmpm   *(0x250f),#34
	bc     0x3a41,ntc
	ld     *(0x2512),b
	and    #512,b
	bc     0x3a41,beq
	ssbx   st1,intm
	portr  56,*(0xb)
	and    #8,b
	bc     0x3a40,beq
	rsbx   st1,intm
	idle   1
	b      0x3a27
	rsbx   st1,intm
	ld     #3,b
	nop
	portw  *(0xb),60
	ld     #5,b
	nop
	portw  *(0xb),60
	stm    #11,brc
	rptb   0x3a51
	nop
	portw  *ar2+,57
	ld     #3,b
	bc     0x3a5e,aneq
	stm    #1,brc
	rptb   0x3a5c
	nop
	portw  *ar2+,57
	nop
	ld     #5,b
	ld     #-4,a
	nop
	portw  *(0x8),60
	ld     #2,a
	nop
	portw  *(0x8),60
	ssbx   st1,intm
	portr  0,*(0x8)
	or     #96,a
	nop
	portw  *(0x8),0
	rpt    #21
	nop
	rsbx   st1,intm
	portr  56,*(0x8)
	and    #16,a
	or     a,b
	nop
	portw  *(0xb),56
	ret
