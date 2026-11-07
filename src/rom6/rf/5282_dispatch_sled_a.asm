; ROM6 0x5282 DISPATCH_SLED_A -- 66w, symbols.yaml data_word.
; Evidence: Bounds 5282-52C3 + 52F7-5300 + 5301-5335 + 5336-5354 + 5355-5361 + 5362-538C + 538D-5394 (branch- entered sled/merge fragments, zero F074 callers; entries via F820/F84D/F830/FA20/B
; ORIGIN 0x5282
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12618,ar0
	stm    #9396,ar1
	stm    #12586,ar2
	stm    #9364,ar3
	stm    #12682,ar4
	stm    #985,ar5
	stm    #12554,ar6
	stm    #9633,ar7
	ld     *ar7,a
	sub    *ar6,a
	bc     0x52aa,alt
	mar    *ar6+
	bc     0x529f,aneq
	dld    *ar0+,a
	dst    a,*ar1+
	bd     0x52af
	mvdd   *ar2+,*ar3+
	mvdd   *ar4+,*ar5+
	mar    *+ar0(0x2)
	ldm    ar6,a
	sub    #12554,a
	sub    *(0x31aa),a
	bcd    0x5292,alt
	mar    *ar2+
	mar    *ar4+
	ld     #0,a
	dst    a,*ar1+
	stl    a,*ar3+
	st     #128,*ar5+
	mar    *ar7+
	ldm    ar7,a
	sub    #9633,a
	sub    *(0x265c),a
	bc     0x52c0,ageq
	ldm    ar6,a
	sub    #12554,a
	sub    *(0x31aa),a
	bc     0x5292,alt
	b      0x52aa
	st     #9633,*(0x245e)
	ret
