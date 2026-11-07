; ROM6 0x69BE SUB_69BE -- 38w, symbols.yaml data_word.
; Evidence: Bound 69BE-69E3 (exit FE00@69E1 + slots 69E2/69E3 = gap end); caller F074@5D83 (call 0x69be); touches existing SUB_69E4, no overlap; HYPOTHESIS.
; ORIGIN 0x69BE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	stm    #1309,ar1
	bitf   *ar1,#512
	rc     ntc
	bitf   *(0x58f),#15
	rc     tc
	cmpm   *(0x2614),#0
	rc     ntc
	stm    #1340,ar2
	cmpm   *ar2,#0
	rc     ntc
	mvdm   0x2a84,ar4
	stm    #9752,ar3
	mvdd   *ar4+,*ar3
	addm   #1,*(0x2a84)
	cmpm   *ar4,#-1
	rcd    ntc
	st     #4,*ar2
	andm   #-513,*ar1
	retd
	orm    #1024,*ar1
