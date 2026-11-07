; ROM6 0x5AC8 SEG_5AC8 -- 51w, symbols.yaml data_word.
; Evidence: Entry F002 2B1C F47E E910 (fall-through); bound 5AC8-5AFA (exit F073@5AF9->5AFD); alt entry 5ACA (same exit, len49, not separately symbolized); join F820@5AC1->5AC8 (conditional, n
; ORIGIN 0x5AC8
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #11036,2,a
	sfta   a,-2
	ld     #16,b
	stlm   b,t
	stlm   a,ar3
	stm    #0,ar5
	stm    #1,ar1
	stm    #3,ar6
	stm    #56,brc
	rptb   0x5aea
	ld     *ar3,ts,a
	and    #15,16,a
	mar    *ar4+0
	sth    a,*ar4
	add    #8,b
	ld     b,a
	and    #15,b
	mar    *+ar0(0x40)%
	xc     1,beq
	ld     #16,b
	sub    b,a
	stlm   b,t
	mvmm   ar2,ar4
	xc     1,aeq
	mar    *ar3+
	mar    *ar5+
	mpy    *(0x15),#57,a
	stlm   a,ar0
	stlm   b,t
	ldm    ar3,a
	cmpm   *(0x250f),#34
	bc     0x5afb,ntc
	sub    *(0x352c),a
	b      0x5afd
