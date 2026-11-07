; ROM6 0x87EB ROUTINE_87EB -- 40w, symbols.yaml data_word.
; Evidence: Bound 87EB-8812 (40w; exit RET FC00@8812 byte-verified, exit scan clean); entries calld F274@86B8-> 87EB byte-verified (in SUB_867E — corroborates its CALLD note, targets head+2) +
; ORIGIN 0x87EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	ssbx   st1,frct
	stm    #-19514,ar1
	stm    #-19530,ar3
	stm    #-19498,ar4
	stm    #-19522,ar5
	stm    #4538,ar6
	stm    #7,brc
	rptbd  0x8810
	stm    #8,ar0
	mvmm   ar6,ar7
	ld     #2,14,a
	rpt    #3
	add    *ar7+0,14,a
	mar    *ar6+
	mpya   *ar3+
	add    *ar1+,16,b
	add    #256,16,b
	sfta   b,-9
	sfta   b,-16
	ld     *ar4+,a
	min    b
	ld     *ar5+,a
	max    b
	sub    a,b
	stl    b,*ar2+
	rsbx   st1,frct
	ret
