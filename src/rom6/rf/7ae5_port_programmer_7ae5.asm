; ROM6 0x7AE5 PORT_PROGRAMMER_7AE5 -- 141w, symbols.yaml data_word.
; Evidence: Entry 60F8 0010 0000 + F920 3D3B confirmed; 8 branch refs (2xF073/3xF820/2xF830/1xF845: count 6 falsified to 8), zero true CALLs; portw PA5/PA7/PA8 @0x7AF8/0x7AFE/0x7B05 + PA33 @0x
; ORIGIN 0x7AE5
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x10),#0
	cc     0x3d3b,ntc
	ld     *(0x578),a
	stl    a,*(0x579)
	stm    #9797,ar5
	ld     *ar1,b
	bcd    0x7b0a,bneq
	sub    #224,b,a
	ld     #15000,b
	nop
	portw  *(0xb),5
	rpt    #22
	nop
	nop
	portw  *(0xb),7
	rpt    #21
	nop
	ld     #0,b
	nop
	portw  *(0xb),8
	rpt    #12
	nop
	bcd    0x7b1b,aneq
	stm    #9786,ar2
	stm    #9782,ar3
	stl    a,*+ar3
	ld     *(0x3e8c),b
	call   0x3c00
	st     #127,*ar5
	bd     0x7b39
	orm    #4,*ar2
	stm    #9782,ar3
	stm    #9535,ar4
	bitf   *ar2,#4
	bcd    0x7b2d,tc
	mar    *ar3+
	mar    *ar4+
	ld     #33,b
	and    *(0x2628),b
	bc     0x7b30,beq
	sub    *ar3,*ar4,a
	bc     0x7b30,aeq
	mvdd   *ar4,*ar3
	andm   #-5,*ar2
	ld     *ar1,a
	bc     0x7b39,aeq
	mvdd   *ar4,*ar5
	ld     *ar3,a
	calld  0x3c00
	ld     *(0x3e8b),b
	ld     #4,b
	calld  0x4007
	ld     *(0x54e),a
	bitf   *(0x3ec8),#32
	bc     0x7b71,ntc
	ld     *(0x2613),a
	sub    #512,a
	stm    #4816,ar2
	bc     0x7b51,alt
	sub    #463,a
	bc     0x7b51,ageq
	stm    #4944,ar2
	ssbx   st1,intm
	portr  33,*(0xb)
	or     #5,b
	and    #-3,b
	nop
	portw  *(0xb),33
	stm    #127,brc
	rptb   0x7b64
	nop
	portw  *ar2+,36
	nop
	portr  33,*(0xb)
	and    #-5,b
	or     #3,b
	nop
	portw  *(0xb),33
	rsbx   st1,intm
	ret
