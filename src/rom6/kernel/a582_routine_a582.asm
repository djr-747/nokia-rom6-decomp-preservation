; ROM6 0xA582 ROUTINE_A582 -- 68w, symbols.yaml data_word.
; Evidence: Bound A582-A5C5 (68w; exit RET FC00@A5C5 byte-verified; interior joins A5A4/A5AD->A5B1; exit scan otherwise clean); entries call F074@B426->A582 byte-verified + post-RET head (FC00
; ORIGIN 0xA582
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x658
	ld     *(0x262a),b
	rc     beq
	stm    #0,ar3
	stm    #-1,ar4
	ld     *(0x2639),a
	calld  0x463b
	and    #256,a
	andm   #-257,*(0x2639)
	stl    a,*(0x262d)
	cmpm   *(0x250f),#34
	bc     0xa5b1,ntc
	stm    #13456,ar2
	ld     *ar2,b
	and    #7,b
	bc     0xa5a6,bneq
	stl    a,*(0x34c4)
	b      0xa5b1
	ld     *ar2,b
	and    #1,b
	bc     0xa5af,beq
	stl    a,*(0x34c5)
	b      0xa5b1
	stl    a,*(0x34c6)
	rc     aeq
	ld     *(0x250f),b
	and    #-2,b
	cmpm   *(0xb),#32
	bc     0xa5c5,ntc
	cmpm   *(0x8),#112
	bc     0xa5c5,tc
	stl    a,*(0x2efd)
	st     #0,*(0x262d)
	ret
