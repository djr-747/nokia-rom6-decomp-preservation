; ROM6 0x88DA FRAG_88DA -- 45w, symbols.yaml data_word.
; Evidence: Bound 88DA-8906 (45w; exit B F073@8905->88AD + operand 8906 — branch-tailed into bounded zone; exit scan otherwise clean); entry B F073@8954->891C byte-verified mid-span (from FRAG
; ORIGIN 0x88DA
	.sect ".text"
	.mmregs
	.global _start
_start:
	andm   #-2,*ar4
	st     #0,*(0x55a)
	andm   #-7,*ar4
	orm    #2,*ar4
	stm    #4491,ar4
	calld  0x86fb
	stm    #12325,ar3
	stm    #17,ar0
	stm    #12325,ar2
	stm    #12432,ar3
	stm    #7,brc
	rptbd  0x88f6
	stm    #4508,ar4
	mvdd   *ar2,*ar3+
	mvdd   *ar2+,*ar4+
	stm    #0,bk
	stm    #12443,ar3
	stm    #3,brc
	rptbd  0x8902
	stm    #12090,ar2
	mvdd   *ar2,*ar3+0%
	mvdd   *ar2+,*ar4+
	call   0x89c4
	b      0x88ad
