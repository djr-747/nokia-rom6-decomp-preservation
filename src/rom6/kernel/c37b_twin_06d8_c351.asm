; ROM6 0xC37B TWIN_06D8_C351 -- 17w, symbols.yaml data_word.
; Evidence: Entry F074 06D8; bounds C351-C37A + C37B-C38B (RET C37A/C38B); callers C187/C1B7; RPTBD MAC / TMPYR lanes; HYPOTHESIS.
; Pool: MPYR round-multiply + RPTBD (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xC37B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6d8
	stm    #11,brc
	stm    #12594,ar2
	rptbd  0xc38a
	stm    #10466,ar3
	ld     *ar2,t
	mpyr   *ar2+,b
	ld     *(0xc),t
	mpyr   *ar3,a
	sth    a,*ar3+
	ret
