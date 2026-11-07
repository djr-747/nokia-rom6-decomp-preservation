; ROM6 0xE5BA LEAF_E5BA -- 23w, symbols.yaml data_word.
; Evidence: Bound E5BA-E5D0 (exit retd FE00@E5CE + delays E5CF-E5D0 byte-verified); entry F074 call @DC72 word- verified + post-retd head (delays 3562/F642); bytes E807 7713 09DA EC52 8291; ab
; ORIGIN 0xE5BA
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #7,a
	stm    #2522,ar1
	rpt    #91
	sth    a,*ar1+
	st     #24576,*ar1+
	rpt    #13
	sth    a,*ar1+
	stl    a,*ar1+
	st     #20,*ar1+
	st     #27083,*ar1+
	st     #18,*(0xa4a)
	st     #1,*(0xa4b)
	retd
	st     #-1,*+ar1
