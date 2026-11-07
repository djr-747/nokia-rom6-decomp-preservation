; ROM6 0xABD2 ROUTINE_ABD2 -- 53w, symbols.yaml data_word.
; Evidence: Bound ABD2-AC06 (53w; exit RET FC00@AC06 byte-verified, exit scan clean); entries 2x calld F274@A50F/A610->ABD2 byte-verified + post-RET head (FC00@ABD1); interior F073-free; abuts
; ORIGIN 0xABD2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x596
	pshm   ar3
	pshm   ar2
	pshm   ar6
	calld  0x71a3
	mvdm   0x22d,ar6
	call   0x71d8
	popm   ar6
	popm   ar2
	popm   ar3
	stm    #1291,ar4
	ld     *ar4,a
	bc     0xac22,aneq
	ld     *ar2,a
	stl    a,*(0x60)
	stm    #31,ar5
	stm    #9633,ar2
	ldm    ar2,b
	add    *(0x265c),b
	sub    #1,b
	stlm   b,ar4
	nop
	nop
	ld     *ar4,b
	sub    a,b
	bc     0xac00,bneq
	bitf   *(0x263a),#4096
	bc     0xac00,ntc
	orm    #1024,*(0x263a)
	sub    *ar2+,a,b
	bc     0xac07,beq
	banz   0xac00,*ar5-
	ret
