; ROM6 0xAC4C PORTSEQ_AC4C -- 111w, symbols.yaml data_word.
; Evidence: Entry F074 0596 76F8 0580 0530 7712; bound AC4C-ACBA (111w); callers F074@2149/2160/2170/2253/A341 (at-site only, upstream alignment unwalked); pa0/pa48/pa3/pa1/pa2 seq + call AE24
; ORIGIN 0xAC4C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x596
	st     #1328,*(0x580)
	stm    #9786,ar2
	bitf   *ar2,#128
	bc     0xad0d,ntc
	st     #0,*(0x13d0)
	andm   #-129,*ar2
	ssbx   st1,intm
	portr  0,*(0xb)
	or     #140,b
	and    #-257,b
	nop
	portw  *(0xb),0
	rpt    #21
	nop
	ld     #256,b
	bitf   *(0x3ec8),#2
	bc     0xac72,ntc
	ld     #180,b
	nop
	portw  *(0xb),48
	nop
	portr  3,*(0xb)
	or     #256,b
	nop
	portw  *(0xb),3
	rpt    #21
	nop
	ld     #4096,b
	nop
	portw  *(0xb),1
	rpt    #22
	nop
	portr  2,*(0xb)
	and    #-4097,b
	nop
	portw  *(0xb),2
	rsbx   st1,intm
	stm    #9786,ar2
	andm   #-97,*ar2
	orm    #64,*ar2
	andm   #-2,*(0x263b)
	bitf   *(0x3ec8),#32
	bc     0xacbb,ntc
	st     #4772,*(0x265e)
	st     #4730,*(0x2660)
	ssbx   st1,intm
	call   0xae24
	rsbx   st1,intm
	stm    #2000,brc
	rptb   0xacb0
	nop
	portr  12,*(0x8)
	or     *(0x3ece),a
	nop
	portw  *(0x8),12
	ret
