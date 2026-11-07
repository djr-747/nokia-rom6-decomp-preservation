; ROM6 0xB5FF FRAG_B5FF -- 6w, symbols.yaml data_word.
; Evidence: Bound B5FF-B604 (10w; exit RET FC00@B604 byte-verified, exit scan clean); post-RET head only (FC00@B5FE, zero ext refs); interior out-call call@B602->06B4; raw B5B9 F845->B5FF (mer
; ORIGIN 0xB5FF
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #3,*(0x4c5)
	call   0x6b4
	ret
