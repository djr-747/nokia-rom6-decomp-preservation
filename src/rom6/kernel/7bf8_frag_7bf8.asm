; ROM6 0x7BF8 FRAG_7BF8 -- 11w, symbols.yaml data_word.
; Evidence: Bound 7BF8-7C02 (11w; exit RET FC00@7C02 byte-verified, exit scan clean); entries post-RET head (FC00@7BF7 = ROUTINE_7B72 exit) + bc F842@7BC9->7BFD byte-verified (from PORT_PROGRA
; ORIGIN 0x7BF8
	.sect ".text"
	.mmregs
	.global _start
_start:
	max    a
	ld     #1023,b
	min    a
	stl    a,*ar1
	stm    #9753,ar2
	ld     #0,a
	rpt    #3
	stl    a,*ar2+
	ret
