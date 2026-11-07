; ROM6 0xB0F5 STUB_B0F5 -- 27w, symbols.yaml data_word.
; Evidence: Entry F074 0678 7713 0914 1083 F110 000D; caller F074@AFAB (objdump call); first-RET @0xB10F (27w); HYPOTHESIS.
; ORIGIN 0xB0F5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x678
	stm    #2324,ar3
	ld     *ar3,a
	sub    #13,a,b
	stm    #12024,ar4
	xc     1,blt
	ld     a,b
	sub    #12,b,a
	bcd    0xb110,aneq
	mpy    *ar4,#4,a
	ld     *ar3,b
	sub    *(0x2652),b
	stm    #8,ar2
	add    #5,a
	xc     1,beq
	stlm   a,ar2
	ret
