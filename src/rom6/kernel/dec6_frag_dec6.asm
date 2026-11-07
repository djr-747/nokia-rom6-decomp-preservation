; ROM6 0xDEC6 FRAG_DEC6 -- 67w, symbols.yaml data_word.
; Evidence: Bound DEC6-DF08 (67w; exit RET FC00@DF08 byte-verified, exit scan clean); post-RET head only (FE00@DEC5, zero ext refs); interior 5x calld DEE2/DEE8->E526 + DEF8->DB3E + DEFE/DF04-
; ORIGIN 0xDEC6
	.sect ".text"
	.mmregs
	.global _start
_start:
	rpt    #9
	stl    a,*ar4+
	rpt    #9
	mvkd   0x1146,*ar4+
	stm    #4412,ar2
	stm    #4422,ar3
	stm    #4362,ar4
	stm    #4432,ar5
	stm    #9,brc
	rptbd  0xdedc
	stm    #4442,ar6
	add    *ar2+,*ar4,a
	add    *ar3+,*ar4+,b
	sth    a,*ar5+
	sth    b,*ar6+
	ld     #0,asm
	ld     #205,16,a
	stm    #103,ar5
	calld  0xe526
	stm    #4432,ar2
	ld     #205,16,a
	calld  0xe526
	stm    #4442,ar2
	bitf   0x62,#4
	bcd    0xdefc,ntc
	stm    #4432,ar2
	stm    #4442,ar3
	stm    #2737,ar4
	stm    #2727,ar5
	calld  0xdb3e
	stm    #2668,ar6
	stm    #4432,ar2
	calld  0xe4cb
	stm    #3996,ar3
	stm    #4442,ar2
	calld  0xe4cb
	stm    #3976,ar3
	ret
