; ROM6 0x87C3 FRAG_87C3 -- 4w, symbols.yaml data_word.
; Evidence: Bound 87C3-87C6 (4w; exit RET FC00@87C6 byte-verified — minimal RET-terminated cell); SIX bc entries byte-verified (cond fan-in: F820@8782/8789 + F84C@8794 + F843@87AD/87BB + F84E@
; ORIGIN 0x87C3
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #1,*(0x3082)
	ret
