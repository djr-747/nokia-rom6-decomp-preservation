; ROM6 0x35C5 LEAF_35C5 -- 68w, symbols.yaml data_word.
; Evidence: Entry 71DA/0578 post-RET; body calls 0x2E2F (F074 35B7/35C7) + 0x3640 (F074 35B5); first-RET FC00 @0x3608; HYPOTHESIS leaf.
; ORIGIN 0x35C5
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdk   *ar2+0%,0x578
	call   0x2e2f
	b      0x2e64
	stm    #9786,ar4
	stm    #1308,ar3
	ldm    ar1,a
	sftl   a,8
	and    #6144,a
	bc     0x35db,aeq
	or     *(0x51f),a
	stl    a,*(0x51f)
	bc     0x35ee,aneq
	bitf   *(0x11),#4
	bc     0x35e4,ntc
	orm    #512,*ar4
	b      0x35ee
	bitf   *(0x11),#2
	bc     0x35ec,ntc
	orm    #2,*ar3
	xc     2,ntc
	orm    #1,*ar3
	bitf   *(0x11),#1
	bc     0x3608,tc
	andm   #-4,*ar3
	andm   #-513,*ar4
	andm   #-6145,*(0x51f)
	ld     *(0x2510),a
	and    #240,a
	sub    #192,a
	bc     0x3608,aneq
	st     #1,*(0x2efe)
	st     #1,*(0xb67)
	ret
