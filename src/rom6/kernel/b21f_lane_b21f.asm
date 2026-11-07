; ROM6 0xB21F LANE_B21F -- 79w, symbols.yaml data_word.
; Evidence: Bound B21F-B26D (79w, exit FC00@B26D); bacc-table arm; F820/F845 fall-throughs to B25A/B245; 2x cc F930 2E64 (objdump cc tc, interior, not entries); out-calls B358/A3E1/A2C3/B431/A
; ORIGIN 0xB21F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xb358
	call   0xa3e1
	call   0xa2c3
	call   0xb431
	call   0xa4d5
	cmpm   *(0x34bf),#4
	bc     0xb25a,ntc
	ld     *(0x34c7),a
	bc     0xb245,aeq
	mvdk   *(0x34c6),0x34c8
	stl    a,*(0x34c6)
	stm    #13456,ar2
	andm   #-16,*ar2
	orm    #2,*ar2
	call   0xb3b1
	mvdk   *(0x34c8),0x34c6
	st     #0,*(0x34c7)
	ld     *(0x37dd),a
	bc     0xb25a,aeq
	ld     *(0x264a),a
	sub    #14304,a
	add    #15072,a
	stlm   a,ar2
	stl    a,*(0x37d9)
	st     #14299,*(0x37db)
	mvdk   *(0x34dd),0x37d7
	mvdk   *ar2,0x37d8
	cmpm   *(0x34bf),#3
	cc     0x2e64,tc
	call   0xb3e2
	st     #0,*(0x37db)
	cmpm   *(0x34bf),#3
	cc     0x2e64,tc
	call   0xa7b7
	call   0xa7eb
	ret
