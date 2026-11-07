; ROM6 0xACF3 FRAG_ACF3 -- 1w, symbols.yaml data_word.
; Evidence: Bound ACF3-ACF3 (1w micro: ld #80,a single word, NO own exit — runs into ROUTINE_ACF4 head; tail-frag abut, not a routine); entry B F073@ACE2->ACF3 byte-verified (exterior from FRA
; ORIGIN 0xACF3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #80,a
