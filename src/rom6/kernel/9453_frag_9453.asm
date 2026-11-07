; ROM6 0x9453 FRAG_9453 -- 6w, symbols.yaml data_word.
; Evidence: Bound 9453-9458 (6w; NO own unconditional exit: calld-lane runs into 9459's span — tail-frag abut, not a routine); entry bc F830@9440->9453 byte-verified (cond tc, exterior from CO
; ORIGIN 0x9453
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0x9a50
	stm    #154,ar4
	bc     0x942e,agt
