; ROM6 0xDB5D SUB_DB5D -- 25w, symbols.yaml data_word.
; Evidence: Entry 767A 0FFF 771A 0009; first exit ret FC00 @DB75; caller F274 @DDC2 verified; HYPOTHESIS.
; ORIGIN 0xDB5D
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #4095,0x7a
	stm    #9,brc
	rptbd  0xdb74
	stm    #10,ar0
	mpy    *ar1+,#16383,a
	mac    *ar2+,#16383,a
	ld     0x7a,t
	mpya   b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mac    *ar3+0,b
	mar    *+ar3(0xffbb)
	sth    b,*ar4+
	ret
