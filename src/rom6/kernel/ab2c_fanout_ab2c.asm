; ROM6 0xAB2C FANOUT_AB2C -- 42w, symbols.yaml data_word.
; Evidence: Entry F074 068C 7712 051C 6182 0080; bound AB2C-AB55 (FC00@AB55); callers F074 @A692/A9B5 (verified); interior calls 068C/AA7C/AB56 x2 (@AB48/AB51 F274)/AAC7; interior bcd@AB40 ntc
; ORIGIN 0xAB2C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x68c
	stm    #1308,ar2
	bitf   *ar2,#128
	bcd    0xab40,ntc
	orm    #128,*ar2
	ld     *(0x914),a
	sub    #4,a
	rc     ageq
	ld     #-16384,a
	and    *ar2,a
	rc     aneq
	rsbx   st0,ovb
	pshm   st0
	pshm   st0
	ssbx   st1,sxm
	call   0xaa7c
	popm   st0
	stm    #632,bk
	calld  0xab56
	stm    #579,ar3
	call   0xaac7
	popm   st0
	nop
	ssbx   st0,ovb
	calld  0xab56
	stm    #1354,ar3
	ret
