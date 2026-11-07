; ROM6 0x3879 FRAG_3879 -- 19w, symbols.yaml data_word.
; Evidence: Bound 3879-388B (19w; exit B F073@388A->37DF + operand 388B, byte-verified; exit scan clean); entry bc F84D@37FE->3879 byte-verified (exterior, FRAG_37D8 interior); vestibule arm 1
; ORIGIN 0x3879
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12032,ar3
	ldm    ar5,b
	sfta   b,-1
	stm    #1,ar0
	bc     0x37df,blt
	rpt    *(0xb)
	mvdd   *ar2+0%,*ar3+
	stm    #154,ar4
	calld  0x2c88
	stm    #12032,ar3
	b      0x37df
