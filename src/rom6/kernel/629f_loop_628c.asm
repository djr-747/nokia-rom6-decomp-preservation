; ROM6 0x629F LOOP_628C -- 21w, symbols.yaml data_word.
; Evidence: Entry F030 FFFF 7E83 6F83; rptbd 0x629A + banz self @0x629B; RET @629F len 21 (wave-11 correction: len-20 arithmetic ended mid-instruction — stm@62B2 operand spills to 62B3; +1w to
; ORIGIN 0x629F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
	cmpm   *ar6,#80
	bc     0x62f2,tc
	cmpm   *ar6,#82
	bc     0x62f2,tc
	calld  0x698b
	stm    #2336,ar1
	calld  0x69a9
	stm    #2336,ar1
	stm    #9769,ar0
	stm    #2335,ar1
