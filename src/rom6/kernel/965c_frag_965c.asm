; ROM6 0x965C FRAG_965C -- 3w, symbols.yaml data_word.
; Evidence: Bound 965C-965E (3w micro-arm: ld #6,a + B F073@965D->9667 + operand 965E, byte-verified; exit scan clean); entry bcd FA4E@963B->965C byte-verified (cond bgt, from dark arm 9629-96
; ORIGIN 0x965C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #6,a
	b      0x9667
