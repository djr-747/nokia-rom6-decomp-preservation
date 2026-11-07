; ROM6 0x69A9 SUB_69A9 -- 21w, symbols.yaml data_word.
; Evidence: Bound 69A9-69BD (exit FE00@69BB + slots 69BC/69BD); callers F274 @62AC/64F6/656E (calld 0x69a9); BCD@69B5 falls through; HYPOTHESIS.
; ORIGIN 0x69A9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	ld     #7,a
	and    *ar1,a
	bitf   *(0x2627),#256
	sub    #3,a,b
	xc     2,tc
	bc     0x69b9,aneq
	bcd    0x69bb,bleq
	ld     #0,b
	nop
	ld     #8,b
	sub    a,b
	retd
	stl    b,*(0x564)
