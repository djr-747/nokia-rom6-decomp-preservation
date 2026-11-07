; ROM6 0x938C COBBA_READ_PREAMBLE -- 66w, symbols.yaml data_word.
; Evidence: CORRECTED entry F074 05BA (no 74xx at 0x938C); PORTR pa0 74 82 00 00 @0x93A4 after STM AR2,#96 @0x93A2 is interior, not entry; sisters pa2 @0x93B4, pa0 @0x93BF; RET FC00 @0x93CD; z
; ORIGIN 0x938C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ba
	st     #2048,*(0x20ff)
	ld     #0,a
	stl    a,*(0x2202)
	stl    a,*(0x2204)
	st     #867,*(0x2203)
	stm    #96,ar2
	st     #128,*ar2
	nop
	portw  *ar2,54
	call   0x9682
	stm    #96,ar2
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #20
	nop
	st     #1792,*ar2
	nop
	portw  *ar2,1
	rpt    #22
	nop
	portr  2,*ar2
	orm    #1792,*ar2
	nop
	portw  *ar2,2
	bitf   *(0x3ec8),#2
	rc     ntc
	portr  0,*ar2
	orm    #16,*ar2
	nop
	portw  *ar2,0
	rpt    #20
	nop
	st     #2,*ar2
	nop
	portw  *ar2,55
	ret
