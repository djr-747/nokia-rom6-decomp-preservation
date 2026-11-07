; ROM6 0x4533 FRAG_4533 -- 28w, symbols.yaml data_word.
; Evidence: Bound 4533-454E (28w; exit RET FC00@454E byte-verified, exit scan clean); entries bc F845@43E1-> 4533 byte-verified (truly exterior, other gap) + sibling call@458D->4533 (gap-sibli
; ORIGIN 0x4533
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	stm    #12032,ar4
	ld     *ar4+,a
	and    #15,a
	mvdk   *ar4+,0x13
	ldu    *ar4+,b
	sftl   b,-8
	stl    b,1,*(0x15)
	sub    #1,b
	stlm   b,ar6
	mar    *+ar5(0x6)
	call   0x454f
	stm    #12032,ar3
	calld  0x2c88
	stm    #116,ar4
	ret
