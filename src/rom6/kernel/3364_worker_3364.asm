; ROM6 0x3364 WORKER_3364 -- 88w, symbols.yaml data_word.
; Evidence: Entry 12D2 F130 (ldu *ar2+%,a; and), post-ret (FC00@3363); bound 3364-33BB (88w, exit F073@33BA->2E64); no interior calls/joins; HYPOTHESIS.
; Pool: 3-word STL-shift-direct 6FF8 053C 0C98 (stl a,-8,*(0x53c)) has no ti-c54x catalog row and no store leaf (all 6F rows are 2-word; stronger unbound than the 6FD2/6FD3 2-word forms); the 0C98 shift word matches the family but the first word matches neither LD_SMEM_SHIFT (6F80/FFE0) nor STH_SHIFT_DIRECT (6F00/FF80). stays .asm, bytes verified.
; ORIGIN 0x3364
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2+%,a
	and    #255,a,b
	stm    #9749,ar4
	stl    a,-8,*(0x53c)
	mvdd   *ar2+0%,*ar4+
	stl    b,*ar4+
	mvdk   *ar2+0%,0x53d
	stm    #1295,ar4
	mvdk   *ar2+0%,0x2618
	st     #0,*ar4
	ld     *(0x53c),a
	sub    #2,a,b
	sub    #3,a
	bc     0x3387,aneq
	bitf   *ar2,#512
	stm    #1359,ar3
	andm   #-4097,*ar3
	xc     2,tc
	orm    #4096,*ar3
	stm    #1311,ar3
	ld     *ar2+%,a
	bitf   *(0x8),#256
	andm   #-257,*ar3
	xc     2,tc
	orm    #256,*ar3
	bc     0x339f,bneq
	and    #255,a
	sub    #10,a,b
	nop
	nop
	xc     1,bgt
	ld     #0,a
	stl    a,*ar4
	stl    a,*(0x510)
	call   0x2e2f
	call   0x5b6
	bitf   *(0x58f),#15
	bc     0x33ba,ntc
	ld     *(0x53c),a
	sub    #4,a
	bc     0x2e64,aneq
	orm    #1,*(0x2453)
	mvkd   0x2616,*(0x2451)
	mvkd   0x2618,*(0x2452)
	st     #0,*(0x53c)
	b      0x2e64
