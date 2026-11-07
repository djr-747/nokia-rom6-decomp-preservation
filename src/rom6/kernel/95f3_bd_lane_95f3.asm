; ROM6 0x95F3 BD_LANE_95F3 -- 22w (dark-gap wave-13, dead).
; Evidence: DEAD past bd 9667 (unconditional delayed branch; delays 95F7-95F8 always run then leave; 95F9+ unreachable linearly, no exterior refs -- dark-entry only). Preceded by bd 9667 + delays (prev span tail). Bound 95F3-9608. Stays asm (no live intent to model; bytes verified). Interior bc 9609 (join next span); bd 9667 x2. Recombine-clean.
; ORIGIN 0x95F3
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar4+%
	ld     #4,a
	bd     0x9667
	mvmd   ar4,0x21fa
	sub    #492,a,b
	bc     0x9609,blt
	ld     #0,a
	st     #0,*(0x20fd)
	mar    *ar4-%
	mar    *ar4-%
	orm    #128,*ar2
	bd     0x9667
	mvmd   ar4,0x21fa
