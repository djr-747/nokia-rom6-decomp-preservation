; ROM6 0x7937 SUB_7937 -- 38w, symbols.yaml data_word.
; Evidence: Entry F074 059E; bound 7937-795C (FC00@795C); callers 3x F274 @7465/74E9/74FD (7465/74E9 word- verified); owns jumped-to delay tail through 7966 (exit FE00@7964 + delays 7965/7966;
; ORIGIN 0x7937
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	pshm   ar6
	pshm   ar0
	stm    #536,ar4
	stm    #1316,ar5
	stm    #4,bk
	mvmm   ar5,ar6
	rptbd  0x7959
	stm    #1,ar0
	call   0x795d
	calld  0x795d
	sth    a,2,*ar3+
	sth    b,2,*ar3+
	neg    a
	calld  0x795d
	sth    b,2,*ar3+
	sth    a,2,*ar3+
	neg    a
	neg    b
	calld  0x795d
	sth    a,2,*ar3+
	sth    b,2,*ar3+
	neg    b
	sth    b,2,*ar3+
	sth    a,2,*ar3+
	popm   ar0
	popm   ar6
	ret
