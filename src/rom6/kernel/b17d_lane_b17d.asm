; ROM6 0xB17D LANE_B17D -- 112w, symbols.yaml data_word.
; Evidence: Bound B17D-B1EC (112w, exit FC00@B1EC); bacc-table arm; 8x cond bc joins to B1B0/B1E8 (F845/F820/F844 verified); out-calls B358/A3E1/A2C3/B431/A4DE/A4D5/B3B1 x3/B3E2/A679/A7B7/A7EB
; ORIGIN 0xB17D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xb358
	call   0xa3e1
	call   0xa2c3
	mvdk   *(0x22d),0x265b
	call   0xb431
	call   0xa4de
	call   0xa4d5
	ld     *(0x914),a
	bc     0xb1b0,aeq
	sub    #13,a
	bc     0xb1b0,aeq
	cmpm   *(0x34bf),#4
	bc     0xb1b0,ntc
	ld     *(0x34c7),a
	bc     0xb1b0,aeq
	mvdk   *(0x34c6),0x34c8
	stl    a,*(0x34c6)
	stm    #13456,ar2
	andm   #-16,*ar2
	orm    #2,*ar2
	call   0xb3b1
	mvdk   *(0x34c8),0x34c6
	st     #0,*(0x34c7)
	call   0xb3e2
	call   0xa679
	ld     *(0x914),a
	sub    #13,a
	bc     0xb1e8,aneq
	ld     *(0x34bf),a
	bc     0xb1e8,aeq
	ld     *(0x34c7),a
	bc     0xb1e8,aeq
	mvdk   *(0x34c5),0x34c8
	stl    a,*(0x34c5)
	stm    #13456,ar2
	andm   #-16,*ar2
	orm    #1,*ar2
	call   0xb3b1
	mvdk   *(0x34c8),0x34c5
	cmpm   *(0x34bf),#4
	bc     0xb1e8,ntc
	mvdk   *(0x34c6),0x34c8
	stm    #13456,ar2
	mvdk   *(0x34c7),0x34c6
	andm   #-16,*ar2
	orm    #2,*ar2
	call   0xb3b1
	mvdk   *(0x34c8),0x34c6
	call   0xa7b7
	call   0xa7eb
	ret
