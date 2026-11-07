; ROM6 0x98AD WRAP_98AD -- 247w, symbols.yaml data_word.
; Evidence: Entry F074 05C8 61F8 3EC8 0002 F820 98BF; callers F074@315A/9460(objdump); first-RET @0x99A3 (247w, spans existing 0x999D poster -- no re-emit, overlap noted); HYPOTHESIS.
; ORIGIN 0x98AD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5c8
	bitf   *(0x3ec8),#2
	bc     0x98bf,ntc
	portr  55,*(0x8)
	and    #8208,a
	or     #4,a
	nop
	portw  *(0x8),55
	stm    #96,ar2
	stm    #8447,ar3
	stm    #8706,ar4
	ld     *ar3,a
	or     *ar4,a
	and    #1792,a,b
	bc     0x98d4,beq
	ld     *(0x2200),a
	rc     aneq
	portr  54,*(0x8)
	and    #4096,a,b
	rc     beq
	ssbx   st1,intm
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #18
	nop
	andm   #-2,*(0x20ff)
	call   0x97a2
	rsbx   st1,intm
	ld     *ar4,a
	and    #1024,a,b
	bc     0x98ed,beq
	bd     0x98fb
	and    #-867,a
	and    #512,a,b
	bc     0x98f5,beq
	bd     0x98fb
	and    #-257,a
	and    #256,a,b
	bc     0x98fb,beq
	and    #-99,a
	stl    a,*ar4
	and    #1792,a,b
	bc     0x990a,beq
	xor    *ar3,b
	and    #1792,b
	bc     0x990a,beq
	ld     *ar3,b
	and    #1792,b
	bc     0x9996,bneq
	ssbx   st1,intm
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #18
	nop
	bitf   *ar3,#128
	bc     0x9929,ntc
	portr  12,*ar2
	pshm   al
	pshm   ah
	pshm   ag
	ld     *(0x3eca),a
	cmpl   a
	and    *ar2,a
	stl    a,*ar2
	popm   ag
	popm   ah
	popm   al
	nop
	portw  *ar2,12
	nop
	portr  54,*ar2
	ld     *ar2,b
	bitf   *ar4,#768
	and    #-511,b
	xc     2,tc
	or     #384,b
	and    #126,a
	or     b,a
	stl    a,*ar2
	nop
	portw  *ar2,54
	ld     *ar4,a
	and    #1950,a
	stl    a,*ar3
	call   0x9682
	ld     *ar3,a
	and    #1792,a
	bitf   *(0x2202),#1
	bcd    0x9950,aneq
	stm    #96,ar2
	ld     #0,a
	xc     2,tc
	stl    a,*(0x2201)
	b      0x9953
	st     #0,*(0x54d)
	rsbx   st1,intm
	ld     *(0x2203),a
	bc     0x995c,aneq
	call   0x9760
	b      0x995e
	call   0x96bd
	call   0x728
	bitf   *(0x2202),#2
	ssbx   st1,intm
	portr  12,*(0x8)
	bitf   *(0x3ec8),#2048
	bc     0x9980,ntc
	portr  28,*(0x8)
	bitf   *(0x2202),#2
	stm    #16076,ar4
	ld     *ar4,b
	or     b,a
	bc     0x997a,ntc
	cmpl   b
	and    b,a
	nop
	portw  *(0x8),28
	b      0x9995
	bitf   *(0x2202),#2
	stm    #16076,ar4
	ld     *ar4,b
	cmpl   b
	and    b,a
	xc     1,tc
	or     *ar4,a
	bitf   *(0x3ec8),#1
	bc     0x9991,ntc
	xor    *(0x3ecc),a
	nop
	portw  *(0x8),12
	rsbx   st1,intm
	ld     #0,a
	bitf   *(0x3ec8),#2
	rcd    ntc
	stl    a,*(0x2202)
	stm    #154,ar4
	stm    #0,ar5
	call   0x2c88
	ret
