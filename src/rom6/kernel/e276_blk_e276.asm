; ROM6 0xE276 BLK_E276 -- 77w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E2C2 (77w); interior exit-class words present mid-stream (alignment- unverified), all-paths walk open; no callers listed; HYPOTHESIS.
; ORIGIN 0xE276
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,dp
	ld     #239,a
	stlm   a,brc
	sth    a,0x17
	stm    #12032,ar6
	ld     #0,asm
	rptbd  0xe282
	mvmm   ar6,ar2
	ld     *ar3+,t
	mpyr   *ar1+,a
	st     a,*ar2+ || ld     *ar3+,t
	rsbx   st0,ova
	mvmm   ar6,ar2
	squr   *ar2+,a
	rpt    #238
	squra  *ar2+,a
	bcd    0xe294,anov
	mvmm   ar6,ar2
	mvmm   ar6,ar3
	ld     #-2,asm
	ld     *ar2+,16,a
	rpt    #239
	st     a,*ar3+ || ld     *ar2+,a
	bd     0xe283
	mar    *+ar7(0x4)
	add    #1,a
	exp    a
	ld     #15,asm
	norm   a
	ldm    t,b
	sth    a,*ar4+
	ldm    al,a
	st     a,*ar4+ || ld     *ar2+,a
	stm    #9,brc
	stm    #236,ar5
	rptbd  0xe2af
	stm    #-237,ar0
	mpy    *ar3+,*ar2+,a
	rpt    0x15
	mac    *ar3+,*ar2+,a
	mac    *ar3+,*ar2+0%,a
	stlm   b,t
	mvmm   ar6,ar3
	norm   a
	sth    a,*ar4+
	ldm    al,a
	st     a,*ar4+ || ld     *ar5-,a
	mar    *ar0+
	ld     #0,asm
	retd
	sub    0x17,b,a
	stm    #9,brc
	rptbd  0xe2c1
	st     #1,0x62
	mpy    *ar3+,*ar2+,b
	mpy    *ar2-,a
	maca   0x62,b
	mpy    *ar3-,*ar2+,a
	maca   0x62,b
	st     b,*ar3+ || ld     *ar2+,t
	ldm    bl,b
	sth    b,15,*ar3+
	ret
