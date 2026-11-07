; ROM6 0xC5C3 MINMAX_TRIO_C5C3 -- 15w, symbols.yaml data_word.
; Evidence: Entry F074 0692; bounds C5C3-C5D1 + C5D2-C5E9 + C5EA-C5F8 (callerless MASR twin); callers C61F calld->C5C3, C636/C638/C642->C5D2; C5F8 abuts C5F9 head; HYPOTHESIS.
; ORIGIN 0xC5C3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x692
	ld     *ar2+,16,a
	rptb   0xc5d0
	abs    a
	mpya   *ar4+
	st     a,*ar3 || mac    *ar3+,b
	sfta   b,-8
	mac    *ar4-,*ar3+,b
	mpyu   *ar3,a
	add    a,-16,b
	stl    b,*ar3-
	st     b,*ar3- || ld     *ar2+,a
	ret
