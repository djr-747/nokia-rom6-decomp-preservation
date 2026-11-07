; ROM6 0x82FE LEAF43_82D4 -- 54w, symbols.yaml data_word.
; Evidence: Entry F6BE EA00 6DEA 0007 E721 7715 0006 E900; RET @82FE len 54; 4 callers F274 @82C2/82CB/8351/8370; no inner calls; extended 8329-8333 (fall-through tail from neg@8328: stl/mar/l
; ORIGIN 0x82FE
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
	rsbx   st1,cpl
	ld     #0,dp
	stm    #6,ar5
	ld     #0,b
	ld     *ar6,13,a
	add    #1,13,a
	sth    a,0x14
	ld     #1,a
	add    *ar6-,a
	and    #7,a
	add    #8,a
	neg    a
	stl    a,0x0e
	mar    *ar4+0
	ld     *ar4,ts,a
	ror    a
	rol    b
	sfta   b,1
	or     *ar1,b
	stl    b,*ar1-
	ld     #0,b
	stm    #7,brc
	rptb   0x832e
	ld     *ar6,13,a
	add    #1,13,a
	sth    a,0x14
	ld     #1,a
	add    *ar6-,a
	and    #7,a
	add    #8,a
	neg    a
	stl    a,0x0e
	mar    *ar4+0
	ld     *ar4,ts,a
	ror    a
	rol    b
	sfta   b,1
	banzd  0x8318,*ar5-
	or     *ar1,b
	stl    b,*ar1-
	ssbx   st1,cpl
