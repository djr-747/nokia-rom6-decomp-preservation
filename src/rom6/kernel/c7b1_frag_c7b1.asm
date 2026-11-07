; ROM6 0xC7B1 FRAG_C7B1 -- 56w, symbols.yaml data_word.
; Evidence: Bound C7B1-C7E8 (56w; REVERSAL of C7B1-C850 noreturn-negative: byte re-scan finds SINGLE F073 in span at C7E7->C878 + operand C7E8, exit scan otherwise clean of RET/FE00/BD/BACC; C
; ORIGIN 0xC7B1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5ec
	st     #512,*(0x8)
	nop
	portw  *(0x8),1
	rpt    #22
	nop
	portr  53,*(0x8)
	st     #0,*(0x20fa)
	stm    #8438,ar7
	stm    #8435,ar6
	stm    #8436,ar5
	mvdm   0x54a,ar4
	cmpm   *ar7,#0
	bc     0xc7d2,tc
	stm    #632,bk
	b      0xc7f6
	bitf   *ar5,#1024
	bc     0xc7e9,tc
	bitf   *ar5,#512
	bc     0xc7e2,tc
	sub    #2,a,b
	bc     0xc8f8,beq
	sub    #258,a,b
	bc     0xc8fe,beq
	and    #256,a,b
	bc     0xc7f8,beq
	stl    a,*ar6
	b      0xc878
