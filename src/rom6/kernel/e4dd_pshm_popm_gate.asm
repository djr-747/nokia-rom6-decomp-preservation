; ROM6 0xE4DD PSHM_POPM_GATE -- 46w, symbols.yaml data_word.
; Evidence: Entry 4A13 4A12 F274 E46B; callers F274 @E4A1(ccd)/E4BF; 2x call E46B; BOUND CORRECTED entry-linear: straight-line to first exit retd @0xE508, bound E4DD-E50A (incl delay); was E52
; ORIGIN 0xE4DD
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar3
	pshm   ar2
	calld  0xe46b
	stm    #4352,ar3
	popm   ar2
	calld  0xe46b
	nop
	mar    *ar2+
	popm   ar3
	ld     #4096,a
	stl    a,*ar3+
	stl    a,0x63
	stm    #4352,ar4
	stm    #4364,ar5
	mvmm   ar3,ar2
	stm    #3,brc
	ld     #-13,asm
	rptbd  0xe500
	mar    *+ar3(0x9)
	dld    *ar5+,a
	drsub  *ar5,a
	dadd   *ar4+,a,b
	dadd   *ar4,b
	adds   0x63,b
	stl    b,asm,*ar2+
	sub    a,1,b
	stl    b,asm,*ar3-
	dld    *ar5+,a
	drsub  *ar5,a
	dadd   *ar4+,a,b
	dadd   *ar4,b
	adds   0x63,b
	stl    b,asm,*ar2+
	sub    a,1,b
	retd
	stl    b,asm,*ar3-
	ld     #0,asm
