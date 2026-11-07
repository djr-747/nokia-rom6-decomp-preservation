; ROM6 0xD571 SUB_D571 -- 16w, symbols.yaml data_word.
; Evidence: Entry E734 771A 0027 949E F58D; calld targets @D63E/@D8B0; first-RET retd @D57E (bound D571-D580); HYPOTHESIS.
; Pool: SQUR square + SQDST distance (both oracle-unbound); stays .asm, bytes verified.
; Pool: SQUR square + SQDST distance (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xD571
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar3,ar4
	stm    #38,brc
	rptbd  0xd579
	ld     *ar3+,14,a
	squr   a,b
	ld     *ar3+,14,a
	sqdst  *ar3,*ar3
	bc     0xd581,bneq
	ldm    ar6,a
	rc     aneq
	retd
	stl    b,*(0xb58)
