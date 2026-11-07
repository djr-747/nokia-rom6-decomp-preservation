; ROM6 0xCED6 ROUTINE_CED6 -- 43w, symbols.yaml data_word.
; Evidence: Bound CED6-CF00 (43w; exit retd FE00@CEFE + architectural delays CEFF-CF00 included per wave-1 convention; exit scan otherwise clean); entries call F074@D1D4->CED6 byte-verified he
; ORIGIN 0xCED6
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #3314,ar2
	stm    #4352,ar3
	ld     #-1,asm
	ld     *ar2+,16,a
	rpt    #39
	st     a,*ar3+ || ld     *ar2+,a
	stm    #3234,ar2
	stm    #4352,ar3
	mvmm   ar3,ar4
	ld     #1,a
	rpt    #39
	mac    *ar2+,*ar3+,a
	exp    a
	st     t,0x63
	norm   a
	sth    a,asm,0x62
	rcd    aleq
	ld     #0,a
	ld     #0,asm
	squr   *ar4+,a
	rpt    #38
	squra  *ar4+,a
	exp    a
	st     t,0x65
	norm   a
	sth    a,0x64
	ld     #5,b
	ld     #16,a
	add    0x63,b
	sub    0x65,b
	min    b
	neg    b
	stlm   b,t
	ld     0x62,16,a
	rpt    #14
	subc   0x64,a
	retd
	stl    a,0x66
	ld     0x66,ts,a
