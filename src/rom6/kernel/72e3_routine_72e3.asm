; ROM6 0x72E3 ROUTINE_72E3 -- 44w, symbols.yaml data_word.
; Evidence: Bound 72E3-730E (44w; exit RET FC00@730E byte-verified, exit scan clean); entries cc F946@71FC-> 72E3 byte-verified (cond call, A815/A91C precedent) + post-RET head (FC00@72E2); in
; ORIGIN 0x72E3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x596
	pshm   ar6
	ld     #12045,a
	add    b,a
	stlm   a,ar5
	sub    #1,a
	stlm   a,ar4
	stm    #12046,ar0
	ld     *ar5,a
	sub    *ar0,a
	bc     0x730d,ageq
	mvmd   ar5,0x17
	sub    #2,b
	stlm   b,brc
	stlm   b,ar6
	rptb   0x730c
	sub    *ar5,*ar4,a
	bc     0x7301,ageq
	ld     *ar5,a
	mvdd   *ar4,*ar5
	stl    a,*ar4
	banzd  0x72fb,*ar6-
	mar    *ar4-
	mar    *ar5-
	mvmd   ar7,0x15
	mvmd   ar7,0x14
	mar    *ar4-
	sub    #1,b
	stlm   b,ar6
	popm   ar6
	ret
