; ROM6 0x66C5 FRAG_66C5 -- 6w, symbols.yaml data_word.
; Evidence: Bound 66C5-66CA (6w; NO own unconditional exit: straight max-lane runs into FRAG_66CB head — tail-frag abut, not a routine); entry bc F84B@66BE->66C5 byte-verified (cond blt, chain
; ORIGIN 0x66C5
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar0,a
	ld     *ar1,b
	max    a
	add    #6,a,b
	add    *ar6,b
