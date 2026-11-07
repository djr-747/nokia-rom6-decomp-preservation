; ROM6 0xAC07 FRAG_AC07 -- 27w, symbols.yaml data_word.
; Evidence: Bound AC07-AC21 (27w; exit RETD FE00@AC1F + delay AC20-21, byte-verified, exit scan otherwise clean); entry bc F84D@AC02->AC07 byte-verified (cond, pre-head exterior) + post-RET he
; ORIGIN 0xAC07
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar5,ar0
	stm    #9395,ar2
	mar    *ar2-0
	addm   #1,*ar2
	stm    #9458,ar4
	mar    *ar4-0
	mar    *ar4-0
	dld    *ar4,a
	add    *ar3,a
	dst    a,*ar4
	ld     *(0x60),b
	pshm   ar0
	calld  0x7067
	stm    #16031,ar3
	popm   ar0
	stm    #1016,ar2
	mar    *ar2-0
	retd
	mvkd   0x60,*ar2
