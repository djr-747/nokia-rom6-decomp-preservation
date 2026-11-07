; ROM6 0x891C FRAG_891C -- 26w, symbols.yaml data_word.
; Evidence: Bound 891C-8935 (26w; exit B F073@8934->88AD + operand 8935, byte-verified (88AD = FRAG_8894 interior [8894-88B8], CODE); exit scan clean); entry B F073@8954->891C byte-verified (e
; ORIGIN 0x891C
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #4491,ar4
	calld  0x86fb
	stm    #12432,ar3
	stm    #0,bk
	stm    #17,ar0
	stm    #12082,ar3
	stm    #12441,ar2
	rpt    #3
	mvdd   *ar3+,*ar2+0%
	stm    #12442,ar2
	rpt    #3
	mvdd   *ar3+,*ar2+0%
	stm    #12443,ar2
	rpt    #3
	mvdd   *ar3+,*ar2+0%
	b      0x88ad
