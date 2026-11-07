; ROM6 0xDBC3 SUB_DBC3 -- 17w, symbols.yaml data_word.
; Evidence: Entry E900 767A 1FFF after retd DBC0; callers F274 @D44F/@DCF1; first-RET ret @DBD3; HYPOTHESIS.
; ORIGIN 0xDBC3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	st     #8191,0x7a
	stm    #6,brc
	rptbd  0xdbd1
	st     #4681,0x7b
	ld     0x7a,t
	mpy    *ar2+,a
	mac    *ar2+,a
	mac    *ar2+,a
	mac    *ar2+,a
	maca   0x7b,b
	ld     b,-16,b
	ret
