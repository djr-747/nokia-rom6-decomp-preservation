; ROM6 0xE42D BLK_E42D-head -- 21w (overlap-split wave-12).
; Evidence: Pool: banzd to exterior E3C7 + delay-slot word have no direct C form (flagged). Bound E42D-E441 (post-RET head; calld E442; banzd/banz loop-back pair to E3C7; retd @E43F + delays E440-E441; assembler warns rpt-in-retd-delay (ROM bytes authoritative)). Former tail E442-E491 duplicated e442/e46b spans (owned there; deleted from this file, 101w -> 21w). Recombine-clean.
; ORIGIN 0xE42D
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar5,ar2
	calld  0xe442
	mvmm   ar6,ar5
	mvmm   ar2,ar6
	banzd  0xe3c7,*ar7-
	sth    a,0x6c
	sth    a,0x6d
	b      0xe43b
	delay  0x6c
	banz   0xe3c7,*ar7-
	mvdm   0x63,ar3
	mvdm   0x62,ar4
	retd
	rpt    #9
	mvdd   *ar3+,*ar4+
