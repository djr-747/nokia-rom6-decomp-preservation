; ROM6 0x5B26 SEG_5B26 -- 54w, symbols.yaml data_word.
; Evidence: Entry F074 0674 10F8 264D; bound 5B26-5B5B (exit F073@5B5A->5BC6); fall-through after FC00@5B25; interior F074 0674 + F274 5BD9 @5B4D/56; incoming join bd@5B9A->5B48; HYPOTHESIS.
; ORIGIN 0x5B26
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x674
	ld     *(0x264d),a
	add    #-20214,a
	stlm   a,ar1
	ld     #0,b
	sth    b,*(0x2f02)
	ld     *ar1,b
	rsbx   st1,cpl
	ld     #0,dp
	ssbx   st1,ovm
	ld     *(0x1d2),16,a
	add    *(0x2622),16,a
	rsbx   st1,ovm
	baccd  b
	sth    a,*(0x2622)
	ssbx   st1,ovm
	ld     *(0x2621),16,a
	add    *(0x1d3),16,a
	sth    a,*(0x2621)
	rsbx   st1,ovm
	stm    #11093,ar1
	stm    #11207,ar0
	pshm   ar1
	ld     #0,a
	stlm   a,ar7
	stm    #-9021,ar5
	calld  0x5bd9
	stm    #352,ar4
	popm   ar0
	stm    #353,ar4
	ld     #1,a
	stlm   a,ar7
	calld  0x5bd9
	stm    #-9021,ar5
	b      0x5bc6
