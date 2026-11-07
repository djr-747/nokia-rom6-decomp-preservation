; ROM6 0xDD77 ABS_ACCUM_DD77 -- 34w, symbols.yaml data_word.
; Evidence: Entry 7712 0062 7713 FBA6 (FBA6 = stm -1114 immediate, not branch -- operand trap avoided); caller F074 @D183 verified; first exit retd FE00 @DD98 +delays (Bound DD99-DD9A, execute
; ORIGIN 0xDD77
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #98,ar2
	stm    #-1114,ar3
	stm    #99,ar4
	stm    #100,ar5
	stl    a,2,*ar2
	sub    *ar2,*ar3+,a
	abs    a
	sth    a,*ar4
	stm    #14,brc
	st     #15,*ar5
	sub    *ar2,*ar3+,a
	rptbd  0xdd90
	abs    a
	sub    *ar4,16,a,b
	srccd  *ar5,blt
	saccd  a,*ar4,blt
	sub    *ar2,*ar3+,a
	abs    a
	sub    *ar4,16,a,b
	ld     #15,a
	sub    *ar5,a
	stl    a,*ar5
	add    #-1114,a
	stlm   a,ar2
	ld     *ar5,16,a
	retd
