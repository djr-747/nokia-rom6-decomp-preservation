; ROM6 0x7DB3 FRAG_7DB3 -- 2w, symbols.yaml data_word.
; Evidence: Bound 7DB3-7DB4 (2w micro: ld #4096,b 2w, NO own exit — runs into FRAG_7DB5 head; tail-frag abut, not a routine); entry B F073@7DAE->7DB3 byte-verified (exterior from SUB_7D74 [7D7
; ORIGIN 0x7DB3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #4096,b
