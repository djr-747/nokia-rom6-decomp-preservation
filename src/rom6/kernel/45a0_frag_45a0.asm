; ROM6 0x45A0 FRAG_45A0 -- 9w, symbols.yaml data_word.
; Evidence: Bound 45A0-45A8 (9w; exit RET FC00@45A8 byte-verified); post-RET head (FC00@459F, zero exterior refs); interior out-call call@45A6->B4A8; chain link; HYPOTHESIS.
; ORIGIN 0x45A0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	orm    #8192,*(0x51f)
	ld     #16,b
	call   0xb461
	ret
