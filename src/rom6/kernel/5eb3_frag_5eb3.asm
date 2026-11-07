; ROM6 0x5EB3 FRAG_5EB3 -- 68w, symbols.yaml data_word.
; Evidence: Bound 5EB3-5EF6 (68w; exit RET FC00@5EF6 byte-verified, exit scan clean); entries bc F820@5E83-> 5EE1 + F843@5E8D->5EE1 + F820@5E92->5EE1 + F820@5EAD->5EB3 head + B F073@5EB1->5EB5
; ORIGIN 0x5EB3
	.sect ".text"
	.mmregs
	.global _start
_start:
	addm   #3538,*ar3+
	stm    #9302,ar2
	dld    *(0x912),a
	dsub   *ar2,a
	sub    #27,a
	ld     #0,b
	stm    #136,ar4
	xc     1,aleq
	ld     #1,b
	stl    b,*ar3
	stm    #12042,ar3
	calld  0x2c88
	stm    #10,ar5
	st     #0,*(0x2615)
	stm    #1309,ar5
	bitf   *ar5,#1024
	bc     0x5ee1,ntc
	andm   #-1025,*ar5
	stm    #143,ar2
	calld  0x2d5e
	stm    #2157,ar3
	bitf   *(0x51e),#16384
	stm    #1359,ar2
	xc     2,tc
	orm    #8,*ar2
	ld     #240,a
	and    *(0x250f),a
	cmpm   *(0x8),#32
	stm    #9751,ar2
	stm    #2324,ar3
	xc     2,ntc
	stm    #2325,ar3
	sub    *ar2,*ar3,a
	stm    #2322,ar2
	stm    #9302,ar3
	xc     2,aeq
	mvdd   *ar2+,*ar3+
	mvdd   *ar2,*ar3
	ret
