; ROM6 0x3674 FRAG_3674 -- 15w, symbols.yaml data_word.
; Evidence: Bound 3674-3682 (15w; exit B F073@3681->2E64 + operand 3682 — branch-tailed, forward shared-tail to dispatch loop; exit scan otherwise clean); post-RET head only (FC00@3673); inter
; ORIGIN 0x3674
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar4,b
	sub    #3,b
	sftl   b,-1
	ld     *ar2+%,a
	stlm   a,ar3
	stm    #1,ar0
	rpt    *(0xb)
	mvdd   *ar2+0%,*ar3+
	call   0x2e2f
	b      0x2e64
