; ROM6 0x82D9 FRAG_82D9 -- 37w, symbols.yaml data_word.
; Evidence: Bound 82D9-82FD (37w; NO own unconditional exit: loop-lane runs into LEAF43_82D4 head — tail-frag abut, not a routine); entry = fall-through abut from SUB232_810A tail [81F1-82D8] 
; ORIGIN 0x82D9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #6,ar5
	ld     #0,b
	ld     *ar6,13,a
	sth    a,0x14
	ld     #7,a
	and    *ar6-,a
	neg    a
	stl    a,0x0e
	mar    *ar4+0
	ld     *ar4,ts,a
	ror    a
	rol    b
	stl    b,*ar2-
	ld     #0,b
	stm    #7,brc
	rptb   0x82f8
	ld     *ar6,13,a
	sth    a,0x14
	ld     #7,a
	and    *ar6-,a
	neg    a
	stl    a,0x0e
	mar    *ar4+0
	ld     *ar4,ts,a
	ror    a
	rol    b
	sfta   b,1
	banzd  0x82e8,*ar5-
	sftl   b,-1
	stl    b,*ar2-
	ssbx   st1,cpl
