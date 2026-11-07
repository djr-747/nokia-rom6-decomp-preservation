; ROM6 0x29B9 FRAG_29B9 -- 26w, symbols.yaml data_word.
; Evidence: Bound 29B9-29D2 (26w; exit B F073@29D1->2A8A + operand 29D2, byte-verified; exit scan clean); entry bc F820@29A0->29B9 byte-verified (cond ntc, exterior from FRAG_2983 interior — w
; ORIGIN 0x29B9
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#2
	bc     0x29d3,ntc
	st     #2048,*ar3
	stm    #4724,ar3
	stm    #4718,ar2
	bitf   *(0x263b),#4
	ld     *(0x3f0f),a
	xc     2,ntc
	ld     *(0x3f10),a
	stl    a,*ar3+
	st     #19072,*ar3-
	addm   #40,*ar2(0x1)
	b      0x2a8a
