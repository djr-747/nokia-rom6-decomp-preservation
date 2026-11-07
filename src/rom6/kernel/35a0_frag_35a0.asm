; ROM6 0x35A0 FRAG_35A0 -- 27w, symbols.yaml data_word.
; Evidence: Bound 35A0-35BA (27w; exit B F073@35B9->2E64 + operand 35BA, byte-verified; exit scan clean); entry bc F820@355A->35A0 byte-verified (cond ntc, thin dark-src from unclaimed arm 355
; ORIGIN 0x35A0
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #4,*(0x54f)
	mvmm   ar2,ar3
	ld     *ar2+%,a
	ld     *ar2,-8,b
	and    #255,b
	stlm   b,ar5
	ld     *ar2+%,b
	and    #255,b
	stlm   b,ar6
	and    #8,a
	stm    #9490,ar4
	xc     2,aneq
	stm    #9545,ar4
	call   0x3640
	call   0x2e2f
	b      0x2e64
