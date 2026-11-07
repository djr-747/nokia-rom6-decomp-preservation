; ROM6 0xC91C ROUTINE_C91C -- 73w, symbols.yaml data_word.
; Evidence: Entry E805 4E62 8010 7717 0004; caller F274 @C906 (objdump calld); first-RET FC00 @C964; RPTBD+MAC *ar4+,*ar5+ +banzd, no subcalls/ports; HYPOTHESIS mac kernel.
; ORIGIN 0xC91C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #5,a
	dst    a,0x62
	stl    a,0x10
	stm    #4,ar7
	ld     #7,a
	stlm   a,brc
	stl    a,0x65
	stm    #4352,ar2
	ld     #0,asm
	ld     #39,16,b
	sth    b,0x64
	pshm   ar7
	sth    b,0x17
	rptbd  0xc939
	ld     #0,b
	mvmm   ar1,ar3
	mvmm   ar6,ar4
	mvmm   ar3,ar5
	ld     #0,a
	rpt    0x17
	mac    *ar4+,*ar5+,a
	st     a,*ar2+ || ld     *ar3+0%,t
	stl    a,*ar2+
	abs    a
	mar    *ar7-0%
	max    b
	addm   #-1,0x64
	popm   ar7
	dld    0x62,a
	add    b,-1,a
	dld    0x64,b
	stl    b,0x1a
	banzd  0xc92a,*ar7-
	mar    *ar1+
	dst    a,0x62
	exp    a
	stm    #4352,ar2
	stm    #3314,ar3
	addm   #-2,*(0xe)
	st     #0,0x66
	stm    #102,ar5
	stm    #4,ar7
	stm    #3,brc
	rptbd  0xc95f
	mvmm   ar3,ar4
	mar    *ar3+
	dld    *ar2+,a
	norm   a
	dld    *ar2+,b
	norm   b
	macr   *ar5,a
	st     a,*ar4+0% || macr   *ar5,b
	sth    b,*ar4+0%
	banzd  0xc955,*ar7-
	stm    #3,brc
	ret
