; ROM6 0x89F4 ROUTINE_89F4 -- 20w, symbols.yaml data_word.
; Evidence: Bound 89F4-8A07 (exit retd FE00@8A05 + slots 8A06-8A07 objdump); callers F074 @8946/89D5/89DC; abuts HELPER_8A08, no overlap; interior bcd->89FB; HYPOTHESIS.
; ORIGIN 0x89F4
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar1,b
	bcd    0x89fb,bgeq
	mpy    *ar1+,#2045,a
	add    #2045,16,a
	mpy    *ar1,#2045,b
	stl    b,*ar1
	add    *ar1-,16,a
	add    #1,a
	stl    a,*ar1+
	sftl   a,12
	sfta   a,8
	sfta   a,-8
	retd
	sfta   a,-12,b
	sth    b,*ar1-
