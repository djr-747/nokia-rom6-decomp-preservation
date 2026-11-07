; ROM6 0x3787 SUB_3779B -- 24w, symbols.yaml program_word.
; Evidence: Bound 3787-379E (24w); entry TRACE (same histogram: 3787 x1, continuation past 3785 dispatch exit); exits b F073@379D->2E64; HYPOTHESIS.
; ORIGIN 0x3787
	.sect ".text"
	.global _start
_start:
	ld     *ar2+0%,a
	andm   #-16,*(0x51f)
	stm    #9787,ar4
	andm   #-241,*ar4
	and    #240,4,a,b
	sftl   b,-4
	or     *ar4,b
	stl    b,*ar4
	and    #31,a
	stl    a,*(0x58b)
	orm    #1,*(0x589)
	call   0x2e2f
	b      0x2e64
