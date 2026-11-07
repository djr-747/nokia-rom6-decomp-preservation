; ROM6 0xB358 DISPATCH_A -- 70w, symbols.yaml data_word.
; Evidence: Entry F074 05A8 F074 A3D5 FC45 7712; exits: rc FC45 (aeq) @B35C + ret FC00 @B39D (true end B39D span 70 kept; head-rc exit new per all-paths walk); 5 callers B17D B1ED B21F B26E B3
; ORIGIN 0xB358
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a8
	call   0xa3d5
	rc     aeq
	stm    #13456,ar2
	ld     *ar2,a
	and    #-113,a
	stl    a,*ar2
	stm    #4,ar0
	stm    #9492,ar2
	stm    #14974,ar3
	stm    #3,brc
	rptb   0xb371
	ld     *ar2+,a
	rpt    #2
	stl    a,*ar3+0
	mar    *+ar3(0xfff5)
	mar    *+ar3(0xfffe)
	stm    #12032,ar2
	mvkd   0x250d,*ar2
	stm    #2,brc
	rptb   0xb382
	ld     *ar3,a
	xor    *ar2,a
	stl    a,*ar3+0
	addm   #1,*ar2
	andm   #7,*ar2
	ssbx   st1,intm
	portr  2,*(0x8)
	and    #-2049,a
	nop
	portw  *(0x8),2
	nop
	ld     #2048,a
	nop
	portw  *(0x8),1
	rpt    #22
	nop
	rsbx   st1,intm
	stm    #2324,ar2
	calld  0x39a4
	stm    #14974,ar3
	ret
