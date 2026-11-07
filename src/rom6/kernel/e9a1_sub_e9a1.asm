; ROM6 0xE9A1 SUB_E9A1 -- 39w, symbols.yaml data_word.
; Evidence: Entry F074 071C; bound E9A1-E9C7 (39w code, FC00@E9C7); caller F074@E6AA (byte-verified call 0xe9a1); straight-line sth-clears + banz loop; out-call 071C only; abuts E9C8 ZEROFILL_
; ORIGIN 0xE9A1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x71c
	frame  -1
	ld     #0,a
	sth    a,*(0x2d33)
	sth    a,*(0x2d32)
	sth    a,*(0x2d31)
	mvdm   0x29a9,ar7
	stm    #11572,ar0
	stm    #-18550,ar1
	ld     #32767,16,b
	mar    *ar7-
	ld     *ar1+,a
	stlm   a,ar2
	ld     *ar0,a
	sftl   a,-8
	add    #2,a
	add    *(0x2d31),a
	stl    a,*(0x2d31)
	ld     *ar0+,a
	and    #255,a
	stl    a,0x0x00
	rpt    0x0x00
	sth    b,*ar2+
	banz   0xe9b4,*ar7-
	frame  1
	ret
