; ROM6 0xB461 RF_MEAS_B461 -- 71w, symbols.yaml data_word.
; Evidence: Entry F074 06B2 61F8 0007 0800 F7BB; first-RET @0xB4A7 (len 71); objdump call 0x6B2 + ssbx intm + andm *(0x51E); 6 callers incl 45A6 53D5 B531 B5FC C875 C8C8 (cross-span); body cal
; ORIGIN 0xB461
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6b2
	bitf   *(0x7),#2048
	ssbx   st1,intm
	andm   #-8193,*(0x51e)
	bc     0xb46f,ntc
	orm    #8192,*(0x51e)
	ld     *(0x4c2),a
	pshm   bl
	pshm   bh
	pshm   bg
	pshm   al
	pshm   ah
	pshm   ag
	bitf   *(0x577),#64
	bc     0xb482,ntc
	stm    #-16372,spc0
	stm    #-16180,spc0
	b      0xb486
	stm    #-16376,spc0
	stm    #-16184,spc0
	portr  0,*(0x8)
	or     #12,a
	nop
	portw  *(0x8),0
	rpt    #20
	nop
	ld     #8,b
	call   0x4055
	or     #1536,a
	call   0x4007
	popm   ag
	popm   ah
	popm   al
	popm   bg
	popm   bh
	popm   bl
	or     a,b
	stl    b,*(0x4c2)
	bitf   *(0x51e),#8192
	bc     0xb4a7,tc
	rsbx   st1,intm
	ret
