; ROM6 0x3806 FRAG_3806 -- 21w, symbols.yaml data_word.
; Evidence: Bound 3806-381A (21w; exit B F073@3819->37DF + operand 381A, byte-verified; exit scan clean); entry bc F84D@37F6->3806 byte-verified (exterior, FRAG_37D8 interior); vestibule arm 2
; ORIGIN 0x3806
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6bc
	stm    #1,ar0
	stm    #2342,ar3
	rpt    #80
	mvdd   *ar2+0%,*ar3+
	stm    #200,bk
	stm    #2342,ar3
	mvdm   0x57d,ar2
	rpt    #80
	mvdd   *ar3+,*ar2+0%
	addm   #1,*(0x57c)
	b      0x37df
