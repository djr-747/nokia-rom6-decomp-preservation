; ROM6 0x36FB FRAG_36FB -- 51w, symbols.yaml data_word.
; Evidence: Bound 36FB-372D (51w + operand; exit F073@372C->2E64); caller bc@36F3; interior calls 05B2/580B/2E2F/2C88; RECLASSIFIED branch-entered label; HYPOTHESIS fragment.
; ORIGIN 0x36FB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b2
	cmpm   *(0x8),#5
	bc     0x372e,ntc
	st     #2,*(0x58f)
	mvdk   *ar2+%,0x29aa
	mvdk   *ar2+%,0x29ab
	mvdk   *ar2+%,0x29b2
	mvdk   *ar2+%,0x29b3
	ldu    *(0x29aa),a
	add    *(0x29ab),a
	stl    a,*(0x29a9)
	mvdk   *ar2+%,0x29b0
	st     #0,*(0x29b1)
	ld     *(0x29a9),a
	sub    #1,a
	rpt    *(0x8)
	mvdk   *ar2+%,0x2d34
	call   0x2e2f
	stm    #10217,ar3
	stm    #158,ar4
	stm    #2,ar5
	st     #8,*ar3
	call   0x2c88
	b      0x2e64
