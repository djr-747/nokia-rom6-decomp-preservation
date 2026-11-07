; ROM6 0x3779 SUB_3779A -- 14w, symbols.yaml program_word.
; Evidence: Bound 3779-3786 (8w); entry TRACE (same histogram: 3779 head x2, rpt/mvdd lane); exits b F073@3785->2E64; HYPOTHESIS.
; ORIGIN 0x3779
	.sect ".text"
	.global _start
_start:
	stm    #11262,ar4
	rpt    #79
	mvdd   *ar2+0%,*ar4+
	st     #0,*(0x58a)
	orm    #2,*(0x589)
	call   0x2e2f
	b      0x2e64
