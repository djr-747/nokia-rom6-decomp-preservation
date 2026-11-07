; ROM6 0x8AA5 ROUTINE_8AA5 -- 36w, symbols.yaml data_word.
; Evidence: Bound 8AA5-8AC8 (40w; exit BD F273@8AC6->8ACE + operand 8AC7, second delay slot spills onto BLOCK_8AC9 head 8AC9 (shared word, coverage-merged, no separate claim); exit scan otherw
; ORIGIN 0x8AA5
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar5(0x3),a
	sub    #15,a,b
	bcd    0x8ab0,bleq
	st     #0,0x2c
	ld     a,-3,a
	sub    0x6f,a
	stl    a,0x2c
	ld     0x2c,a
	ld     *ar5(0x3),b
	sub    a,3,b
	stl    b,0x2d
	bcd    0x8aca,beq
	st     #8,0x29
	stm    #2,brc
	rptb   0x8ac5
	add    0x6e,b
	bcd    0x8ac6,bgt
	ld     0x2d,b
	nop
	sfta   b,1
	add    0x6f,b
	sub    0x6f,a
	stl    b,0x2d
	bd     0x8ace
	rsbx   st1,braf
