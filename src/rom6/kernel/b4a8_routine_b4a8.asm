; ROM6 0xB4A8 ROUTINE_B4A8 -- 80w, symbols.yaml data_word.
; Evidence: Bound B4A8-B4F7 (80w; exit RET FC00@B4F7 byte-verified; interior join B@B4DD->B4E1; exit scan otherwise clean); entries 5x head-exact byte-verified: F074@2011/45AF/5444/B655 + CC F
; ORIGIN 0xB4A8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6b2
	bitf   *(0x7),#2048
	ssbx   st1,intm
	andm   #-8193,*(0x51e)
	bc     0xb4b6,ntc
	orm    #8192,*(0x51e)
	ld     *(0x4c2),a
	xor    #65535,b
	and    b,a
	stl    a,*(0x4c2)
	bitf   *(0x51e),#8192
	bc     0xb4c3,tc
	rsbx   st1,intm
	rc     aneq
	bitf   *(0x7),#2048
	ssbx   st1,intm
	andm   #-8193,*(0x51e)
	bc     0xb4d0,ntc
	orm    #8192,*(0x51e)
	pshm   bl
	pshm   bh
	pshm   bg
	pshm   al
	pshm   ah
	pshm   ag
	bitf   *(0x577),#64
	bc     0xb4df,ntc
	stm    #-16372,spc0
	b      0xb4e1
	stm    #-16376,spc0
	ld     #8,b
	call   0x4055
	and    #2559,a
	call   0x4007
	popm   ag
	popm   ah
	popm   al
	popm   bg
	popm   bh
	popm   bl
	bitf   *(0x51e),#8192
	bc     0xb4f4,tc
	rsbx   st1,intm
	orm    #16,*(0x0)
	ret
