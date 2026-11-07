; ROM6 0x7ADE FRAG_7ADE -- 7w, symbols.yaml data_word.
; Evidence: Bound 7ADE-7AE4 (7w; NO own unconditional exit: straight lane runs into 7AE5's span — tail-frag abut, not a routine); entry bc F845@7ACA->7ADE byte-verified (cond aeq, exterior fro
; ORIGIN 0x7ADE
	.sect ".text"
	.mmregs
	.global _start
_start:
	mar    *ar0+
	ld     *(0x34cc),a
	bc     0x7ae5,aeq
	stm    #13502,ar3
