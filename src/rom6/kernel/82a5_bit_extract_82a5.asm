; ROM6 0x82A5 BIT_EXTRACT_82A5 -- 16w, symbols.yaml data_word.
; Evidence: Entry 4582 448A 1B92 F2C2 F2C3 F2C5; first exit retd FE00 @82B4 +delay F2C3 8294 thru 82B6; callers F274 @8225/8292 + F074 @825A verified; HYPOTHESIS.
; Wave-13: retd delays @82B5-82B6 annexed (gap orphan; delays always run).
; ORIGIN 0x82A5
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,16,b
	ld     *ar2-,16,a
	or     *ar2+,b
	xor    b,2,a
	xor    b,3,a
	xor    b,5,a
	xor    b,6,a
	sth    a,*ar4+
	ld     *ar2-,16,a
	xor    b,1,a
	xor    b,4,a
	xor    b,6,a
	xc     1,tc
	sth    a,*ar4+
	xor    b,2,a
	retd
	xor    b,3,a
	sth    a,*ar4+
