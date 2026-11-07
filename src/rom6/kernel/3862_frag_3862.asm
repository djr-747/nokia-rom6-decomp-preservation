; ROM6 0x3862 FRAG_3862 -- 23w, symbols.yaml data_word.
; Evidence: Bound 3862-3878 (23w; exit B F073@3877->37DF + operand 3878, byte-verified; exit scan clean); entries bc F84C@37EB->3862 (exterior, FRAG_37D8 interior) + B F073@3800->3862 (FRAG_37
; ORIGIN 0x3862
	.sect ".text"
	.mmregs
	.global _start
_start:
	mar    *+ar2(0xfffd)%
	stm    #12032,ar3
	ldm    ar5,a
	add    #5,a
	sfta   a,-1
	bc     0x386f,alt
	rpt    *(0x8)
	mvdd   *ar2+0%,*ar3+
	stm    #12032,ar3
	mar    *+ar5(0x6)
	calld  0x2c88
	stm    #142,ar4
	b      0x37df
