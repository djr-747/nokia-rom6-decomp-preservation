; ROM6 0xA954 FRAG_A954 -- 70w, symbols.yaml data_word.
; Evidence: Bound A954-A999 (70w; exit RET FC00@A999 byte-verified, exit scan clean); post-RET head only (FC00@A953 = ROUTINE_A91C exit, zero ext refs); interior 12 out-calls incl call@A954->0
; ORIGIN 0xA954
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x686
	bitf   *(0x263a),#512
	rc     tc
	call   0x877d
	stm    #2920,ar2
	andm   #-5,*ar2
	ld     *(0x9c6),a
	orm    #8,*ar2
	xc     2,aeq
	andm   #-9,*ar2
	andm   #-14337,*(0x9cd)
	call   0xd8f6
	ld     *(0x3082),b
	or     b,a
	stl    a,*(0x3082)
	stl    a,*(0x3043)
	bitf   *(0x51c),#3
	bc     0xa99a,tc
	call   0xd90b
	call   0x68a
	stm    #12694,ar1
	rpt    #159
	mvkd   0x3088,*ar1+
	call   0x9e2f
	calld  0xbbef
	stm    #12694,ar2
	calld  0x9fcf
	stm    #10380,ar6
	call   0xa12b
	calld  0x9f42
	stm    #159,brc
	calld  0x6a2
	stm    #12694,ar2
	calld  0xbadb
	stm    #12694,ar2
	ret
