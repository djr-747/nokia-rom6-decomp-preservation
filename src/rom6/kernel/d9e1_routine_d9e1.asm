; ROM6 0xD9E1 ROUTINE_D9E1 -- 27w, symbols.yaml data_word.
; Evidence: Bound D9E1-D9FB (27w; exit RETD FE00@D9F9 + delays D9FA-D9FB (rpt/sth 2w), byte-verified; exit scan clean); entry call F074@DC74->D9E1 byte-verified (exterior from SUB_DC43 interio
; ORIGIN 0xD9E1
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #7,b
	stm    #2648,ar2
	stl    b,*ar2+
	st     #32767,*ar2+
	st     #3,*ar2+
	sth    b,*ar2+
	st     #28801,*ar2+
	st     #26968,*ar2+
	stm    #2662,ar2
	stm    #6,brc
	rptbd  0xd9f8
	rpt    #5
	sth    b,*ar2+
	rpt    #9
	mvpd   0xd9c9,*ar2+
	retd
	rpt    #27
	sth    b,*ar2+
