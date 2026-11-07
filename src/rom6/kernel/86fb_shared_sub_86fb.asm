; ROM6 0x86FB SHARED_SUB_86FB -- 48w, symbols.yaml data_word.
; Evidence: Entry F074 0590 F6B8 E735 F071 004B 8095 7715; EXIT CORRECTED by all-paths walk: sole exit retd FE00 @8728 +2 delay (andm 6883 7FFF); true end 872A span 48 (not 130); banz @8723 lo
; ORIGIN 0x86FB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	rsbx   st1,sxm
	mvmm   ar3,ar5
	rptz   a,#75
	stl    a,*ar5+
	stm    #96,ar5
	st     #15,*ar5
	stm    #97,ar0
	st     #1,*ar0
	stm    #16,ar6
	stm    #-19903,ar1
	stm    #15,brc
	ld     *ar4+,16,b
	rptb   0x8722
	rol    b
	bc     0x8722,nc
	ld     *ar1,a
	and    *ar5,a
	xor    *ar5,a
	stlm   a,t
	ldm    ar3,a
	add    *ar1,-8,a
	stlm   a,ar2
	ld     *ar0,ts,a
	nop
	or     *ar2,a
	stl    a,*ar2
	mar    *ar1+
	banz   0x870e,*ar6-
	ssbx   st1,sxm
	andm   #8191,*ar3+
	retd
	andm   #32767,*ar3
