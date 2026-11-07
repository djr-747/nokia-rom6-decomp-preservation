; ROM6 0x71D8 SCALE_3EB8_LEAF -- 16w, symbols.yaml data_word.
; Evidence: Entry F074 0598; bound 71D8-71E7; callers 758E/ABDB; (577-585)*(*(3EB8))>>8 + *ar3; HYPOTHESIS.
; ORIGIN 0x71D8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	bitf   *(0x3eb5),#16
	rc     ntc
	ld     *(0x578),16,a
	sub    *(0x585),16,a
	mpya   *(0x3eb8)
	sfta   b,-8
	add    *ar3,b
	stl    b,*ar3
	ret
