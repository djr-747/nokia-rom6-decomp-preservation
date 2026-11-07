; ROM6 0x88B9 FRAG_88B9 -- 33w, symbols.yaml data_word.
; Evidence: Bound 88B9-88D9 (33w; exit B F073@88D8->88AD + operand 88D9 — branch-tailed into HEAD_8854 zone; exit scan otherwise clean); post-RET head only (FC00@88B8, zero exterior refs — thi
; ORIGIN 0x88B9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	calld  0x86fb
	stm    #12432,ar3
	stm    #1310,ar4
	stm    #0,bk
	andm   #-2,*ar4
	mvmd   bk,0x55a
	andm   #-7,*ar4
	calld  0x89c4
	orm    #2,*ar4
	stm    #4508,ar3
	rpt    #7
	mvkd   0x3090,*ar3+
	stm    #17,ar0
	stm    #12443,ar2
	rpt    #3
	mvdd   *ar2+0%,*ar3+
	b      0x88ad
