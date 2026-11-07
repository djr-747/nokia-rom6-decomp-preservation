; ROM6 0x95BF BD_LANE_95BF -- 35w (dark-gap wave-13, dead).
; Evidence: DEAD past bd 9667 (unconditional delayed branch; delays 95BD-95BE always run then leave; 95BF+ unreachable linearly, no exterior refs -- dark-entry only). Bound 95BF-95E1. Stays asm (no live intent to model; bytes verified). Interior bc 95EA/95E2 (joins); bd 9667 x2. Recombine-clean.
; ORIGIN 0x95BF
	.sect ".text"
	.mmregs
	.global _start
_start:
	sftl   a,-8
	ld     *ar4,b
	or     a,b
	stl    b,*ar4+%
	mvmd   ar4,0x21fa
	ld     #3,a
	bd     0x9667
	andm   #-129,*ar2
	and    #-256,a,b
	and    #-513,b
	sub    #7168,b
	bc     0x95ea,beq
	orm    #128,*ar2
	and    #255,a
	and    #-3,a,b
	sub    #28,b
	bc     0x95e2,beq
	ld     #0,a
	ld     #0,b
	bd     0x9667
	stl    b,*(0x20fd)
