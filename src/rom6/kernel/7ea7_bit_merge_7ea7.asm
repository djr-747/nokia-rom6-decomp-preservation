; ROM6 0x7EA7 BIT_MERGE_7EA7 -- 10w, symbols.yaml data_word.
; Evidence: Entry 448A F540 1B92 F2C3 F2C4 458A; first exit retd FE00 @7EB0 +delay F2C0 828C thru 7EB2 entry- linear; callers F274 @7E92/7FE4 verified; HYPOTHESIS.
; ORIGIN 0x7EA7
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2-,16,a
	ld     a,b
	or     *ar2+,b
	xor    b,3,a
	xor    b,4,a
	ld     *ar2-,16,b
	or     *ar2,b
	sfta   b,1
	sth    a,*ar4+
	retd
