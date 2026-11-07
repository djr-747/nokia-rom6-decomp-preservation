; ROM6 0x8675 SPAN_HEAD_8675 -- 9w, symbols.yaml data_word.
; Evidence: Span 0x8674 head: F074 0592 76F8 10FE 0017 E800 FE00 80F8; EXIT CORRECTED by all-paths walk: sole exit retd FE00 @867B +2 delay (stl 80F8 10FF); true end 867D span 9 (not 90); stra
; ORIGIN 0x8675
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x592
	st     #23,*(0x10fe)
	ld     #0,a
	retd
	stl    a,*(0x10ff)
