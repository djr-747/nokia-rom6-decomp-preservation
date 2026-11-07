; ROM6 0x45C2 FRAG_45C2 -- 56w, symbols.yaml data_word.
; Evidence: Bound 45C2-45F9 (56w; exit RET FC00@45F9 byte-verified, exit scan clean); post-RET head (FC00@45C1); head 7713 2F00; interior out-calls call@45D3->2E2F + call@45D5->8529 + calld@45
; ORIGIN 0x45C2
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12032,ar3
	st     #13618,*ar3+
	st     #0,*ar3+
	mvmm   ar3,ar4
	stm    #1,ar0
	stm    #11,brc
	stm    #12046,ar5
	rptb   0x45d2
	mvdd   *ar2,*ar5+
	mvdd   *ar2+0%,*ar3+
	call   0x2e2f
	call   0x8529
	calld  0x8529
	stm    #12040,ar4
	ldu    *(0x2f07),a
	xor    *(0xb779),a
	ldu    *(0x2f0d),b
	xor    *(0xb779),b
	or     b,a
	stm    #1274,ar3
	andm   #-5,*ar3
	xc     2,aeq
	orm    #4,*ar3
	st     #0,*(0x2f07)
	st     #0,*(0x2f0d)
	stm    #12032,ar3
	stm    #116,ar4
	calld  0x2c88
	stm    #52,ar5
	ret
