; ROM6 0xE8E4 RPTBD_PREOP -- 43w, symbols.yaml data_word.
; Evidence: Entry 771A 000F F272 E90D 7710 0009 4482; caller F074 @E948; first-RET @E90E (43w); HYPOTHESIS.
; ORIGIN 0xE8E4
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #15,brc
	rptbd  0xe90d
	stm    #9,ar0
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	sth    b,asm,*ar3+
	mpy    *ar3+,a
	mac    *ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	sth    b,asm,*ar2+
	ld     *ar2+,16,a
	sub    *ar2-,*ar3+,b
	add    *ar3-,16,a
	sth    a,asm,*ar2+
	sth    b,asm,*ar2+
	add    *ar3,16,b
	add    *ar3+,16,b
	sub    *ar3,16,a
	sub    *ar3-,16,a
	sth    a,asm,*ar3+
	st     b,*ar3+ || ld     *ar2,a
	mpy    *ar3+,a
	mas    *ar3-,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	st     b,*ar2+ || mac    *ar3,a
	mac    *ar3,a
	add    *ar2,16,a,b
	st     b,*ar3+0% || sub    *ar2,b
	sth    b,asm,*ar2+0%
	ret
