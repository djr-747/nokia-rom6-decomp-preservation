; ROM6 0x45A9 FRAG_45A9 -- 9w, symbols.yaml data_word.
; Evidence: Bound 45A9-45B1 (9w; exit RET FC00@45B1 byte-verified); post-RET head (FC00@45A8); interior out-calls call@45A9->2E2F + calld@45AF->B4A8; chain link; HYPOTHESIS.
; ORIGIN 0x45A9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x2e2f
	andm   #-8193,*(0x51f)
	ld     #16,b
	call   0xb4a8
	ret
