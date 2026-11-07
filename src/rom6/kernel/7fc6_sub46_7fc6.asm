; ROM6 0x7FC6 SUB46_7FC6 -- 22w, symbols.yaml data_word.
; Evidence: Entry F074 059E 6DEA 0007 771A 0003; BOUND CORRECTED entry-linear: straight-line to first exit retd @0x7FD9, bound 7FC6-7FDB (incl delay); was 7FF3 (overclaim; 0x7FD4 FC00 is opera
; ORIGIN 0x7FC6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	mar    *+ar2(0x7)
	stm    #3,brc
	rptb   0x7fd1
	ld     *ar2-,16,b
	or     *ar2+,b
	sfta   b,2
	sth    b,*ar2-
	ld     *ar2,b
	and    #-512,b
	sfta   b,2
	ld     *ar2,a
	and    #511,a
	retd
	or     a,b
	stl    b,*ar2
