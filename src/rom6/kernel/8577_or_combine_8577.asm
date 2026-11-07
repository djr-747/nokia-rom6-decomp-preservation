; ROM6 0x8577 OR_COMBINE_8577 -- 17w, symbols.yaml data_word.
; Evidence: Entry 4492 1A82 458A 1B82 6F92 0D96; first exit ret FC00 @8587; callers F074 @8545/854B verified; HYPOTHESIS.
; ORIGIN 0x8577
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+,16,a
	or     *ar2,a
	ld     *ar2-,16,b
	or     *ar2,b
	stl    b,-10,*ar2+
	stl    a,-10,*ar2-
	ld     *ar3+,16,a
	or     *ar3,a
	ld     *ar3-,16,b
	or     *ar3,b
	stl    a,-15,*ar3+
	stl    b,-15,*ar3-
	ret
