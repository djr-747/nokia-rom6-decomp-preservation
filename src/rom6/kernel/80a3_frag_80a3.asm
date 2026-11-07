; ROM6 0x80A3 FRAG_80A3 -- 80w, symbols.yaml data_word.
; Evidence: Bound 80A3-80F2 (80w; exit RET FC00@80F2 byte-verified, exit scan clean); entry bc F830@7C96->80A3 byte-verified (branch-led, hence FRAG despite F074 head idiom); head F074 059E; i
; ORIGIN 0x80A3
	.sect ".text"
	.mmregs
	.global _start
_start:
	; @80A3 f074 call   0x59e
	call   0x59e
	; @80A5 e905 ld     #5,b
	ld     #5,b
	; @80A6 10f8 ld     *(0x2646),a
	ld     *(0x2646),a
	; @80A8 f945 cc     0x4590,aeq
	cc     0x4590,aeq
	; @80AA 7713 stm    #9482,ar3
	stm    #9482,ar3
	; @80AC 7712 stm    #12036,ar2
	stm    #12036,ar2
	; @80AE e510 mvdd   *ar3,*ar2
	mvdd   *ar3,*ar2
	; @80AF f074 call   0x80f3
	call   0x80f3
	; @80B1 f274 calld  0x80f3
	calld  0x80f3
	; @80B3 7712 stm    #9799,ar2
	stm    #9799,ar2
	; @80B5 770e stm    #0,t
	stm    #0,t
	; @80B7 771a stm    #7,brc
	stm    #7,brc
	; @80B9 f272 rptbd  0x80c7
	rptbd  0x80c7
	; @80BB e900 ld     #0,b
	ld     #0,b
	; @80BC 1082 ld     *ar2,a
	ld     *ar2,a
	; @80BD 8860 stlm   a,96
	stlm   a,96
	; @80BE f2c0 xor    b,a
	xor    b,a
	; @80BF 34f8 bitt   *(0x8)
	bitt   *(0x8)
	; @80C1 f820 bc     0x80c5,ntc
	bc     0x80c5,ntc
	; @80C3 f350 xor    #56832,b
	xor    #56832,b
	; @80C5 4860 ldm    96,a
	ldm    96,a
	; @80C6 f461 sfta   a,1
	sfta   a,1
	; @80C7 f761 sfta   b,1
	sfta   b,1
	; @80C8 f793 cmpl   b
	cmpl   b
	; @80C9 7712 stm    #12035,ar2
	stm    #12035,ar2
	; @80CB 8182 stl    b,*ar2
	stl    b,*ar2
	; @80CC f074 call   0x80f3
	call   0x80f3
	; @80CE f274 calld  0x80f3
	calld  0x80f3
	; @80D0 7712 stm    #9799,ar2
	stm    #9799,ar2
	; @80D2 11f8 ld     *(0x2f04),b
	ld     *(0x2f04),b
	; @80D4 f776 sfta   b,-10
	sfta   b,-10
	; @80D5 7712 stm    #12035,ar2
	stm    #12035,ar2
	; @80D7 1d82 xor    *ar2,b
	xor    *ar2,b
	; @80D8 f330 and    #63,b
	and    #63,b
	; @80DA 8182 stl    b,*ar2
	stl    b,*ar2
	; @80DB 1082 ld     *ar2,a
	ld     *ar2,a
	; @80DC f030 and    #63,a
	and    #63,a
	; @80DE f468 sfta   a,8
	sfta   a,8
	; @80DF 1af8 or     *(0x2647),a
	or     *(0x2647),a
	; @80E1 7712 stm    #12033,ar2
	stm    #12033,ar2
	; @80E3 8092 stl    a,*ar2+
	stl    a,*ar2+
	; @80E4 7682 st     #0,*ar2
	st     #0,*ar2
	; @80E6 76f8 st     #0,*(0x2646)
	st     #0,*(0x2646)
	; @80E9 76f8 st     #0,*(0x2f00)
	st     #0,*(0x2f00)
	; @80EC 7713 stm    #10887,ar3
	stm    #10887,ar3
	; @80EE f274 calld  0x7fdc
	calld  0x7fdc
	; @80F0 7711 stm    #1,ar1
	stm    #1,ar1
	; @80F2 fc00 ret
	ret
