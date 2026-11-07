; ROM6 0x8B03 ROUTINE_8B03 -- 45w, symbols.yaml data_word.
; Evidence: Bound 8B03-8B2F (45w; exit RET FC00@8B2F byte-verified, exit scan clean); entries call F074@8A6B-> 8B03 byte-verified + post-RET head (FC00@8B02); interior rptbd F272@8B20->8B25; H
; ORIGIN 0x8B03
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar5,a
	ld     *ar5+,b
	sub    #40,a
	stm    #4361,ar3
	xc     1,alt
	ld     *ar3,b
	sub    #80,a
	stm    #39,brc
	xc     1,agt
	ld     *ar3,b
	stl    b,*ar3
	ld     #-19490,a
	add    *ar5-,a
	stlm   a,ar2
	ld     #4491,a
	sub    *ar3,a
	stlm   a,ar3
	mvdk   *ar2,0x2f2c
	stm    #12078,ar2
	mvmd   ar4,0x2f2d
	rptbd  0x8b25
	ld     *ar2+,16,b
	ld     0x2c,t
	macr   *ar3+,b
	st     b,*ar4+ || ld     *ar2+,b
	stm    #4371,ar2
	rpt    #79
	mvkd   0x113b,*ar2+
	mvdm   0x2f2d,ar3
	rpt    #39
	mvdd   *ar3+,*ar2+
	ret
