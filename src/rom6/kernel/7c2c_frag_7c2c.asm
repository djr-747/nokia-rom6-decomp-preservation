; ROM6 0x7C2C FRAG_7C2C -- 3w, symbols.yaml data_word.
; Evidence: Bound 7C2C-7C2E (3w; exit B F073@7C2D->7BEE + operand 7C2E — branch-tailed back into ROUTINE_7B72; micro-span, entry+exit verified); entry bc F84B@7C22->7C2C byte-verified (from FR
; ORIGIN 0x7C2C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #1,a
	b      0x7bee
