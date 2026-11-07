; ROM6 0x5B5C FRAG_5B5C -- 66w, symbols.yaml data_word.
; Evidence: Bound 5B5C-5B9D (66w; exit BD F273@5B9A->5B48 + delays 5B9C-5B9D (7710 2B55 execute as delays) — outside gap, end 5B9D per pc+3; exit scan otherwise clean); entries B F073@5BB0->5B
; ORIGIN 0x5B5C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,ovm
	ld     *(0x2621),16,a
	add    *(0x1d3),16,a
	sth    a,*(0x2621)
	rsbx   st1,ovm
	stm    #11093,ar1
	stm    #11207,ar0
	pshm   ar1
	ld     #150,a
	sth    a,0x17
	stm    #-8964,ar5
	calld  0x5bd9
	stm    #352,ar4
	popm   ar0
	stm    #353,ar4
	mar    *ar7+
	ld     #151,a
	calld  0x5bd9
	stm    #-8964,ar5
	ld     *(0x2ef5),a
	bc     0x5bb2,aneq
	st     #192,*(0x2f02)
	ld     *(0x2621),a
	bc     0x5bb2,ageq
	st     #177,*(0x2f02)
	b      0x5bb2
	ssbx   st1,ovm
	add    *(0x1d3),16,a
	sth    a,*(0x2622)
	rsbx   st1,ovm
	st     #0,*(0x2621)
	stm    #11207,ar3
	stm    #11036,ar2
	mvmm   ar2,ar1
	rpt    #56
	mvdd   *ar3+,*ar2+
	bd     0x5b48
	stm    #11093,ar0
