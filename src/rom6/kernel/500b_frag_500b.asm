; ROM6 0x500B FRAG_500B -- 80w, symbols.yaml data_word.
; Evidence: Bound 500B-505A (FC00@505A); abuts bd-delay, zero callers; interior b@5028->505A + b@5046/5050->5056; HYPOTHESIS fragment.
; ORIGIN 0x500B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	bitf   *(0x3aca),#2
	bc     0x502a,ntc
	ld     *(0x3aca),a
	and    #1792,a
	ld     *(0x3490),b
	and    #7,b
	neg    b
	add    a,-8,b
	bc     0x505a,bneq
	ld     *(0x3aca),a
	and    #224,a
	bc     0x5048,aeq
	sub    #1,5,a
	bc     0x5034,aeq
	b      0x505a
	ld     *(0x3490),b
	and    #7,b,a
	bc     0x5048,aeq
	and    #1,b,a
	bc     0x505a,aeq
	cmpm   *(0x34bf),#1
	bc     0x5048,tc
	cmpm   *(0x34bf),#4
	bc     0x5048,tc
	stm    #9801,ar3
	orm    #16,*ar3
	stm    #13555,ar3
	mvkd   0x2f1f,*ar3+
	b      0x5056
	stm    #9800,ar3
	orm    #16,*ar3
	stm    #9593,ar3
	mvkd   0x2f1f,*ar3+
	b      0x5056
	stm    #9665,ar3
	mvkd   0x2f1f,*ar3+
	stm    #12160,ar2
	rpt    #18
	mvdd   *ar2+,*ar3+
	ret
