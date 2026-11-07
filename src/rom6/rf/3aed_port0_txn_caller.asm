; ROM6 0x3AED PORT0_TXN_CALLER -- 247w, symbols.yaml data_word.
; Evidence: Entry F074 0634; bound 3AED-3BE3 (terminal RET raw+full-disasm); caller F074@291C; calls 4007/4055 + calld 4007x2; pa12/pa33; HYPOTHESIS.
; ORIGIN 0x3AED
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x634
	bitf   *(0x3ec8),#32
	bc     0x3b1f,ntc
	ld     #2064,a
	ld     #13,b
	call   0x4007
	ld     #11,b
	call   0x4055
	calld  0x4007
	or     #64,a
	bitf   *(0x3ec8),#8192
	ld     #512,a
	xc     2,tc
	ld     #519,a
	nop
	calld  0x4007
	ld     #3,b
	nop
	bitf   *(0x3ec8),#8
	bc     0x3b1f,ntc
	bitf   *(0x263b),#4
	ld     *(0x583),a
	xc     2,ntc
	ld     *(0x584),a
	sub    #512,a
	ld     #3,b
	call   0x4007
	portr  12,*(0xb)
	bitf   *(0x3eb5),#64
	bc     0x3b46,ntc
	ldu    *(0x3ebc),a
	bitf   *(0x8),#-32768
	and    #32767,a
	sub    *(0x2636),a
	pshm   al
	pshm   ah
	pshm   ag
	ld     *(0x3ecb),a
	cmpl   a
	and    a,b
	popm   ag
	popm   ah
	popm   al
	bc     0x3b42,tc
	bc     0x3b46,agt
	or     *(0x3ecb),b
	b      0x3b46
	bc     0x3b46,aleq
	or     *(0x3ecb),b
	nop
	portw  *(0xb),12
	ld     *(0x3e8f),-2,a
	add    *(0x3e90),-2,a
	bitf   *(0x51f),#128
	bc     0x3b71,ntc
	ld     *(0x2613),b
	sub    #512,b
	bc     0x3b71,blt
	sub    #463,b
	bc     0x3b71,bgeq
	ld     *(0x3eda),-2,a
	add    *(0x3edb),-2,a
	ld     *(0x2636),b
	sub    *(0x3ee6),b
	bc     0x3b71,blt
	ld     *(0x3ee4),-2,a
	add    *(0x3ee5),-2,a
	and    #15,a
	sub    #16,a
	portr  33,*(0xb)
	or     #2560,b
	and    #-1025,b
	nop
	portw  *(0xb),33
	stlm   a,t
	rsbx   st1,sxm
	call   0x3be4
	bc     0x3b8a,tc
	stm    #5,brc
	b      0x3b8c
	stm    #2,brc
	rptbd  0x3bac
	ld     #-1,a
	mvdk   *ar2,0x9
	norm   a
	nop
	portw  *(0x8),39
	sftl   a,-12
	nop
	portw  *(0x8),39
	ld     *ar2+,a
	mvdk   *ar2+,0x9
	mvdk   *ar2,0xa
	sfta   a,-8
	norm   a
	nop
	portw  *(0x8),39
	sftl   a,-12
	nop
	portw  *(0x8),39
	ld     *ar2+,a
	stm    #255,ag
	mvdk   *ar2,0x9
	norm   a
	nop
	portw  *(0x8),39
	sfta   a,-12
	nop
	portw  *(0x8),39
	call   0x3be4
	bc     0x3bd1,tc
	ld     *ar2+,a
	mvdk   *ar2+,0x9
	stm    #255,ag
	sfta   a,-8
	norm   a
	nop
	portw  *(0x8),39
	sftl   a,-12
	nop
	portw  *(0x8),39
	b      0x3bd7
	sfta   a,-12
	nop
	portw  *(0x8),39
	nop
	portr  33,*(0x8)
	and    #-2049,a
	or     #1536,a
	nop
	portw  *(0x8),33
	ssbx   st1,sxm
	ret
