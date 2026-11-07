; ROM6 0x5823 FRAG_5823 -- 2w, symbols.yaml data_word.
; Evidence: Bound 5823-5824 (F5BC ssbx + FC00 ret residual, precedes SUB_5825 head; existing SIEVE_580B ends 5822); HYPOTHESIS fragment.
; ORIGIN 0x5823
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st0,tc
	ret
