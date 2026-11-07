; ROM6 0xCEB4 ROUTINE_CEB4 -- 34w, symbols.yaml data_word.
; Evidence: Entry 7212 0ECD 771A 0004 F272 CEC3; caller F274 @C919 (dispatcher); BOUND CORRECTED entry-linear: straight-line to first exit retd @0xCED3, bound 0xCEB4-0xCED5 (incl 2 delay slots
; ORIGIN 0xCEB4
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0xecd,ar2
	stm    #4,brc
	rptbd  0xcec3
	stm    #-270,ar1
	ld     #7,a
	and    *ar2,a
	adds   0x11,a
	stlm   a,ar3
	ld     #8,a
	and    *ar2,a
	or     *ar3,a
	stl    a,*ar2+
	stm    #3,brc
	ld     #7,b
	mvmm   ar2,ar4
	ld     *ar2+,a
	and    b,a
	rptbd  0xced2
	adds   0x11,a
	stlm   a,ar3
	ld     *ar2+,a
	and    b,a
	mvdd   *ar3,*ar4+
	adds   0x11,a
	stlm   a,ar3
	retd
	nop
	mvdd   *ar3,*ar4
