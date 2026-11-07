; ROM6 0x8DDB ROUTINE_8DDB -- 42w, symbols.yaml data_word.
; Evidence: Bound 8DDB-8E04 (42w; exit RET FC00@8E04 byte-verified, exit scan clean); entries call F074@8D46-> 8DDB head byte-verified + 3x calld F274@8D62/8D80/8D99->8DDC mid-span + post-RET 
; ORIGIN 0x8DDB
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar3+,16,a
	stm    #1,ar0
	stm    #16,bk
	stm    #12096,ar2
	rpt    #7
	mvdk   *ar2+,0x2f48
	rptbd  0x8e02
	stm    #12096,ar2
	sth    a,*ar5+
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+ || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+,b
	st     b,*ar5+0% || macr   *ar4+,a
	ld     *ar4,16,b
	macar  *ar2+%,b
	macr   *ar4+%,a
	st     a,*ar3 || ld     *ar3+,a
	sth    a,0x21
	ret
