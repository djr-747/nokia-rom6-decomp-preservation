; ROM6 0x573B SUB_573B -- 26w, symbols.yaml data_word.
; Evidence: Bound 573B-5754 (exit FC00@5754); caller F074@51FC (call 0x573b); BCD@5745 falls through; preceded by FC00@573A; HYPOTHESIS.
; ORIGIN 0x573B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #2328,ar2
	ld     #240,a
	and    *(0x250f),a
	cmpm   *(0x8),#32
	bcd    0x574f,tc
	ld     *(0x2651),b
	stm    #2327,ar2
	cmpm   *(0x2510),#128
	rc     ntc
	sub    *ar2,b
	rc     bneq
	orm    #32,*(0x2628)
	ret
