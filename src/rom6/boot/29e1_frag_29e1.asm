; ROM6 0x29E1 FRAG_29E1 -- 33w, symbols.yaml data_word.
; Evidence: Bound 29E1-2A01 (33w; exit B F073@2A00->2A8A + operand 2A01, byte-verified; exit scan clean); entry bc F820@29D5->29E1 byte-verified (cond ntc, chained from FRAG_29D3 interior); ve
; ORIGIN 0x29E1
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#4
	bc     0x2a02,ntc
	ld     *(0x1278),a
	and    #224,a
	bcd    0x2a02,aneq
	st     #4096,*ar3
	stm    #4726,ar3
	orm    #-32768,*ar3
	ld     *(0x1271),a
	add    *(0x3f11),a
	sub    *(0x36a),a,b
	nop
	nop
	xc     1,bgeq
	ld     b,a
	stl    a,*(0x1271)
	stm    #4720,ar2
	b      0x2a8a
