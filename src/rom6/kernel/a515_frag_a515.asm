; ROM6 0xA515 FRAG_A515 -- 109w, symbols.yaml data_word.
; Evidence: Bound A515-A581 (103w; exit RET FC00@A581 byte-verified; interior join A568->A56D; exit scan otherwise clean); post-RET head only (FC00@A514, zero ext calls/branches — single-entry
; ORIGIN 0xA515
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x658
	stm    #9785,ar2
	ld     *ar2,a
	and    #8,a
	bc     0xa524,aneq
	ld     *(0x262a),b
	rc     beq
	sub    #160,b,a
	rc     aeq
	stm    #0,ar3
	stm    #-1,ar4
	ld     *ar2,a
	and    #8,a
	bc     0xa537,aeq
	ld     *(0x36d),a
	sub    *(0x250d),a
	andm   #-9,*ar2
	ld     #160,b
	xc     2,alt
	stm    #0,ar4
	ld     *(0x2639),a
	calld  0x463b
	and    #256,a
	andm   #-257,*(0x2639)
	stm    #9773,ar2
	stl    a,*ar2
	bitf   *(0x3eb5),#512
	bc     0xa579,ntc
	bitf   *(0x586),#2
	bc     0xa579,ntc
	pshm   al
	pshm   ah
	pshm   ag
	ld     *(0x261f),b
	andm   #-9,*(0x586)
	bc     0xa56a,beq
	sub    #2,b
	bc     0xa56d,bneq
	stm    #4,bk
	mvdm   0x264b,ar3
	nop
	mar    *ar3-%
	ld     *ar3-%,b
	ld     *ar3-%,a
	min    b
	sub    *(0x3ec5),b
	bc     0xa56a,bgeq
	b      0xa56d
	orm    #8,*(0x586)
	bitf   *(0x586),#8
	bc     0xa576,tc
	ld     #0,a
	stm    #9773,ar2
	stl    a,*ar2
	popm   ag
	popm   ah
	popm   al
	sub    #96,a
	rc     aneq
	cmpm   *(0x250f),#81
	rc     ntc
	stl    a,*ar2
	ret
