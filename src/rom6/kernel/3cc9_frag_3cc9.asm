; ROM6 0x3CC9 FRAG_3CC9 -- 9w, symbols.yaml data_word.
; Evidence: Bound 3CC9-3CD1 (9w; exit RET FC00@3CD1 byte-verified, exit scan clean); entries B F073@3C1A-> 3CC9 byte-verified (from the 3C00 to 3CC8 span) + post-RET head (FC00@3CC8); no inter
; ORIGIN 0x3CC9
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #15000,a
	nop
	portw  *(0x8),7
	rpt    #17
	nop
	ret
