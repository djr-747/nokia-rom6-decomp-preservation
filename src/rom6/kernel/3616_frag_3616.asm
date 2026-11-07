; ROM6 0x3616 FRAG_3616 -- 6w, symbols.yaml data_word.
; Evidence: Bound 3616-361B (6w; exit RET FC00@361B byte-verified; minimal RET-terminated cell); post-RET head only (FC00@3615, zero exterior refs); no interior ops; tail 361C-363F stays dark;
; ORIGIN 0x3616
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1284,ar4
	rpt    #6
	st     #64,*ar4+
	ret
