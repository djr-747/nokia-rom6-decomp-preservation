; ROM6 0x62B4 FRAG_62B4 -- 62w, symbols.yaml data_word.
; Evidence: Bound 62B4-62F1 (62w; exit BD F273@62EE->634F + operand 62EF + delays 62F0-62F1 (orm 2w), byte-verified; 634F = interior of claimed 62F2-63D7 span, CODE; exit scan clean); entry = 
; ORIGIN 0x62B4
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9751,ar5
	ld     *(0x563),a
	bc     0x62c8,aneq
	stm    #3,brc
	rptbd  0x62c7
	ld     *(0x2642),16,a
	sub    *ar1,16,a,b
	add    #1,16,a
	xc     2,beq
	orm    #1,*ar0
	bc     0x634f,beq
	bitf   *(0x51e),#8
	bc     0x62f2,ntc
	ld     *(0x564),a
	bc     0x62f2,aneq
	stm    #4,brc
	rptbd  0x62db
	ld     *(0x565),16,a
	sub    *ar1,16,a,b
	bc     0x62e5,beq
	add    #1,16,a
	ld     *(0x36d),b
	sub    *(0x250d),b
	bc     0x62f2,bgeq
	sub    *ar1,16,a
	bc     0x62f2,aneq
	bitf   *(0x54f),#1024
	bc     0x62ee,ntc
	ld     *(0x545),a
	bc     0x62f2,aeq
	bd     0x634f
	orm    #4096,*ar0
