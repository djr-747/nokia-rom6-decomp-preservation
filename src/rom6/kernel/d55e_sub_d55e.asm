; ROM6 0xD55E SUB_D55E -- 19w, symbols.yaml data_word.
; Evidence: Entry 771A 0026 E723 7712 0B66; calld target @D622; first-RET retd @D56E (bound D55E-D570); HYPOTHESIS.
; ORIGIN 0xD55E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #38,brc
	mvmm   ar2,ar3
	rptbd  0xd568
	ld     *ar2-,a
	stl    a,0x04
	mpy    *ar2-,b
	sub    b,-16,a
	stl    a,*ar3-
	ld     *ar3,a
	stm    #2918,ar2
	mpy    *ar2,b
	sub    b,-16,a
	stl    a,*ar3
	retd
	mvkd   0x3004,*ar2
