; ROM6 0x4B81 SUB_4B81 -- 25w, symbols.yaml data_word.
; Evidence: Entry F6B8 (post-ret head, FC00@4B80); bound 4B81-4B99 (exit F073@4B98->4BA6 + operand); caller F074@4AD4 (byte-verified call 0x4b81, gap-internal); HYPOTHESIS.
; ORIGIN 0x4B81
	.sect ".text"
	.mmregs
	.global _start
_start:
	rsbx   st1,sxm
	ld     *(0x250d),a
	stm    #1169,ar2
	bc     0x4b9a,aeq
	sub    #4,a
	bc     0x4b9a,aeq
	andm   #4095,*ar2+
	stm    #9,brc
	rptb   0x4b97
	ld     *ar2-,12,a
	or     *ar2,a
	stl    a,*ar2+
	ld     *ar2,-4,a
	stl    a,*ar2+
	b      0x4ba6
