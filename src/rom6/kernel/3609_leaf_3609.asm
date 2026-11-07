; ROM6 0x3609 LEAF_3609 -- 13w, symbols.yaml data_word.
; Evidence: Bound 3609-3615 (13w, ret FC00@3615); post-ret head of LEAF_35C5 (RET@3608); zero callers; HYPOTHESIS.
; ORIGIN 0x3609
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x11),a
	stm    #1308,ar4
	orm    #4096,*ar4
	bc     0x3616,aneq
	andm   #12223,*ar4
	orm    #32,*ar4
	ret
