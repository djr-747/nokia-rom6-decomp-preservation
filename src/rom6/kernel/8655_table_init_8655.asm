; ROM6 0x8655 TABLE_INIT_8655 -- 32w (dark-gap wave-13).
; Evidence: Post-call head (prev 8653 call 592); no exterior refs, entry unconfirmed. Bound 8655-8674 (andm; stm; rpt/mvkd fill; stm; rptb 8663 nested rpt/mvkd; stm; rpt/mvkd; rptz/stl fill; stl; stm; calld 86E3 (delay stm runs first); ret @8674). C intent in 8655_table_init_8655.c. Recombine-clean.
; ORIGIN 0x8655
	.sect ".text"
	.mmregs
	.global _start
_start:
	andm   #-8,*(0x51e)
	stm    #12325,ar2
	rpt    #24
	mvkd   0xb373,*ar2+
	stm    #2,brc
	rptb   0x8663
	rpt    #16
	mvkd   0xb37b,*ar2+
	stm    #4508,ar2
	rpt    #7
	mvkd   0xb373,*ar2+
	rptz   a,#3
	stl    a,*ar2+
	stl    a,*(0x55a)
	stm    #12325,ar3
	calld  0x86e3
	stm    #4491,ar4
	ret
