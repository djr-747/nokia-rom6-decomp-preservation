; ROM6 0x8F97 ROUTINE_8F97 -- 23w, symbols.yaml data_word.
; Evidence: Bound 8F97-8FAD (23w; exit retd FE00@8FAB + delays 7691/FFFF 8FAC-8FAD included per convention; exit scan clean); entries call F074@8645->8F97 byte-verified (from MSG_BUILDER_8641)
; ORIGIN 0x8F97
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #7,a
	stm    #2522,ar1
	rpt    #91
	sth    a,*ar1+
	st     #24576,*ar1+
	st     #-16384,*ar1+
	st     #4096,*ar1+
	rpt    #11
	sth    a,*ar1+
	stl    a,*ar1+
	st     #20,*ar1+
	st     #31250,*ar1+
	st     #40,*ar1+
	retd
	st     #-1,*ar1+
