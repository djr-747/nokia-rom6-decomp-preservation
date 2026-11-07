; ROM6 0x8F1C FRAG_8F1C -- 4w, symbols.yaml data_word.
; Evidence: Bound 8F1C-8F1F (4w micro: st DP+0x42 + st DP+0x43 lane, NO own exit — runs into 8F20's span; tail-frag abut, not a routine); entry bcd FA4D@8F07->8F1C byte-verified (cond beq, ext
; ORIGIN 0x8F1C
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-4,0x42
	st     #15,0x43
