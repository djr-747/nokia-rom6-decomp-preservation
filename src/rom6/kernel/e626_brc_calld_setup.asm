; ROM6 0xE626 BRC_CALLD_SETUP -- 38w, symbols.yaml data_word.
; Evidence: Entry 7713 0A4A 771A 0001 A210 F272 E63A; internal F361/F600/F010 lane; first-RET @E64B (38w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE626
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2634,ar3
	stm    #1,brc
	sub    *ar3,*ar2,a
	rptbd  0xe63a
	stm    #0,ar1
	mvmm   ar2,ar4
	mvmm   ar3,ar5
	xc     2,aleq
	mvmm   ar2,ar5
	mvmm   ar3,ar4
	sub    *ar5,*ar4,b
	sub    #2,16,b
	mvdd   *ar2+,*ar3
	sub    *ar3,*ar2,a
	xc     1,blt
	mar    *ar1+
	ld     *(0xa43),a
	stl    a,*(0xa44)
	ldm    ar1,b
	stl    b,*(0xa43)
	add    b,a
	sub    #4,a
	stm    #2635,ar3
	ld     #1,b
	stl    b,*ar3
	xc     1,alt
	sth    b,*ar3
	ret
