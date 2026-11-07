; ROM6 0xC351 TWIN_06D8_C351 -- 42w, symbols.yaml data_word.
; Evidence: Entry F074 06D8; bounds C351-C37A + C37B-C38B (RET C37A/C38B); callers C187/C1B7; RPTBD MAC / TMPYR lanes; HYPOTHESIS.
; ORIGIN 0xC351
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6d8
	ld     0x40,asm
	stm    #11,brc
	stm    #12570,ar2
	stm    #12582,ar3
	st     #512,*(0x3152)
	xor    b
	rptbd  0xc364
	stm    #12626,ar4
	sub    *ar2+,*ar4,a
	sth    a,*ar3
	saccd  b,*ar3+,alt
	stm    #11,brc
	stm    #10466,ar2
	stm    #12582,ar3
	stm    #12645,ar5
	rptbd  0xc374
	stm    #12644,ar4
	mpy    *ar3,*ar5,a
	adds   0x42,a
	mac    *ar2+,*ar4,a
	sth    a,*ar3+
	stm    #10466,ar2
	rpt    #11
	mvkd   0x311a,*ar2+
	ret
