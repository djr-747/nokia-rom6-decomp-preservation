; ROM6 0xB308 LANE_B308 -- 62w, symbols.yaml data_word.
; Evidence: Bound B308-B345 (62w, exit FC00@B345); bacc-table arm; F820/F845 fall-throughs to B330/B341; out- calls A2C3/B358/A3E1/B431/A4D5/B3E2/B3B1 x2/A7B7/A7EB; HYPOTHESIS.
; ORIGIN 0xB308
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xb358
	call   0xa3e1
	call   0xb431
	call   0xa4d5
	call   0xb3e2
	cmpm   *(0x34bf),#4
	bc     0xb330,ntc
	ld     *(0x34c7),a
	bc     0xb330,aeq
	mvdk   *(0x34c6),0x34c8
	stl    a,*(0x34c6)
	stm    #13456,ar2
	andm   #-16,*ar2
	orm    #2,*ar2
	call   0xb3b1
	mvdk   *(0x34c8),0x34c6
	st     #0,*(0x34c7)
	andm   #-16,*(0x3490)
	call   0xb3b1
	ld     *(0x34bf),a
	bc     0xb341,aeq
	mvdk   *(0x34c5),0x34c7
	ld     #0,a
	stl    a,*(0x34c5)
	stl    a,*(0x34c6)
	call   0xa7b7
	call   0xa7eb
	ret
