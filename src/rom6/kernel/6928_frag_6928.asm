; ROM6 0x6928 FRAG_6928 -- 4w, symbols.yaml data_word.
; Evidence: Bound 6928-692B (4w; exit RET FC00@692B byte-verified, exit scan clean; micro-span); entries 3x bc F830@6909/6918/6923->6928 byte-verified (all in SUB_68CA span); pre-word 0100 (re
; ORIGIN 0x6928
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #1,*(0x545)
	ret
