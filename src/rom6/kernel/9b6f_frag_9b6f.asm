; ROM6 0x9B6F FRAG_9B6F -- 3w, symbols.yaml data_word.
; Evidence: Bound 9B6F-9B71 (3w micro: ld + mar + RETD FE00@9B71, byte-verified; exit scan clean; RETD delays 9B72-9B73 belong to FRAG_9B72 head — shared words per 8AA5 precedent, coverage-mer
; ORIGIN 0x9B6F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+,b
	mar    *ar4-
	retd
