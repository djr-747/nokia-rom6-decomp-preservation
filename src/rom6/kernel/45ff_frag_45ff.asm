; ROM6 0x45FF FRAG_45FF -- 60w, symbols.yaml data_word.
; Evidence: Bound 45FF-463A (60w; exit RET FC00@463A byte-verified, exit scan clean); post-RET head (FC00@45FE — 5w dark sliver 45FA-45FE precedes); interior out-calls call@45FF->06F6 + call@4
; ORIGIN 0x45FF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6f6
	stm    #12032,ar3
	rpt    #2
	mvdd   *ar2+0%,*ar3+
	call   0x2e2f
	stm    #1263,ar2
	stm    #12052,ar3
	stm    #5,brc
	rptb   0x4612
	ld     *ar2+,a
	xor    #42405,a
	stl    a,*ar3+
	st     #0,*(0x2f14)
	calld  0x8534
	stm    #12052,ar4
	stm    #2,brc
	stm    #12052,ar4
	andm   #-256,*(0x2f16)
	stm    #12032,ar5
	ld     #0,b
	rptb   0x462e
	ld     *ar4+,a
	and    #30583,a
	xor    *ar5+,a
	nop
	nop
	xc     2,aneq
	ld     #256,b
	stm    #12032,ar3
	st     #13826,*ar3+
	stl    b,*ar3-
	stm    #116,ar4
	calld  0x2c88
	stm    #4,ar5
	ret
