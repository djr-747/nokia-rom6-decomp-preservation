; ROM6 0x7D60 SUB_7D60 -- 20w, symbols.yaml data_word.
; Evidence: Entry 10F8 0914 08F8 2EF8 7717 264F; zero callers; xc-conditionals only; first exit ret @7D73 (abuts 0x7D74); bound 7D60-7D73; HYPOTHESIS.
; ORIGIN 0x7D60
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x914),a
	sub    *(0x2ef8),a
	stm    #9807,ar7
	st     #2,*ar7
	sub    #8,a,b
	xc     1,aeq
	stl    a,*ar7
	sub    #17,a
	xc     1,beq
	stl    b,*ar7
	xc     1,aeq
	stl    a,*ar7
	ld     *ar7,a
	ret
