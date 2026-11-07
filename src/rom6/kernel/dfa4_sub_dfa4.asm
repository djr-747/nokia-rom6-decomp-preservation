; ROM6 0xDFA4 SUB_DFA4 -- 43w, symbols.yaml data_word.
; Evidence: Entry E724 771A 0007 after retd DFA1; callers F274 @DDDC/DDF2/DDF8; first-RET ret @DFCE; HYPOTHESIS.
; ORIGIN 0xDFA4
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar2,ar4
	stm    #7,brc
	rptbd  0xdfac
	mar    *ar2+
	mvdd   *ar2+,*ar3+
	sub    *ar2+,*ar4+,a
	sth    a,*ar3+
	ld     #16384,b
	sub    *ar4,b
	stl    b,*ar3
	mar    *+ar3(0xfff7)
	stm    #104,ar5
	mvmm   ar5,ar4
	stm    #9,brc
	stm    #12,ar2
	st     #1843,*ar5+
	st     #6242,*ar5+
	st     #28160,*ar5+
	rptbd  0xdfcd
	st     #3427,*ar5-
	sub    *ar3,*ar4+,a
	bcd    0xdfcb,ageq
	mpya   *ar4-
	ld     *ar4,16,a
	mpy    *ar3,*ar5+,b
	ld     *ar5-,16,a
	sub    *ar2,16,a
	sfta   a,3
	sth    a,*ar3+
	ret
