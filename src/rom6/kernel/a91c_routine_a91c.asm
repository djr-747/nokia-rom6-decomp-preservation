; ROM6 0xA91C ROUTINE_A91C -- 56w, symbols.yaml data_word.
; Evidence: Bound A91C-A953 (56w; exit RET FC00@A953 byte-verified, exit scan clean); entries 2x cc F94D@B13A + F944@B165->A91C byte-verified (far backward CC refs, AE/B0-arm zone) + post-RET 
; ORIGIN 0xA91C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x686
	bitf   *(0x263a),#512
	rc     tc
	ld     *(0xb67),a
	rc     aneq
	bitf   *(0x51c),#3
	bc     0xa93b,tc
	ld     #3,a
	calld  0xd0be
	stl    a,*(0xecc)
	bitf   *(0xa5a),#1
	stm    #1310,ar2
	orm    #256,*ar2
	xc     2,ntc
	andm   #-257,*ar2
	b      0xa946
	orm    #256,*(0x51e)
	orm    #1,*(0xa5a)
	stm    #3798,ar4
	rpt    #56
	mvkd   0x2799,*ar4+
	call   0xd29e
	calld  0x872b
	stm    #9593,ar4
	or     *(0x257e),a
	stl    a,*(0x257e)
	st     #193,*(0x25a0)
	ret
