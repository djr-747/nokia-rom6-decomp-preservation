; ROM6 0x28A5 FRAG_28A5 -- 42w, symbols.yaml data_word.
; Evidence: Bound 28A5-28CE (exit BACC F5E2@28CE byte-verified bacc-b; computed target unknown, 28CE/STRETCH_2800-precedent caveat); entry bc F830@2897->28A5 byte-verified (backward cond, in F
; ORIGIN 0x28A5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x732
	stm    #1346,ar3
	stm    #1350,ar4
	add    *ar3,*ar4,b
	sftl   b,-16
	stlm   b,ar4
	addm   #1,*ar3
	ldu    *ar4,b
	stm    #1351,ar4
	add    *ar3,*ar4,a
	sftl   a,-16
	stlm   a,ar4
	nop
	nop
	ldu    *ar4,a
	call   0x734
	nop
	portw  *(0x8),15
	rpt    #2
	nop
	ld     *ar3+,a
	orm    #2,*(0x263a)
	sub    *ar3,a
	bc     0x28cb,ageq
	andm   #-3,*(0x263a)
	xc     2,aeq
	st     #0,*ar3
	bacc   b
