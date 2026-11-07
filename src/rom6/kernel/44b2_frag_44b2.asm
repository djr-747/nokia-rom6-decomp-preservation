; ROM6 0x44B2 FRAG_44B2 -- 11w, symbols.yaml data_word.
; Evidence: Bound 44B2-44BC (11w; exit RET FC00@44BC byte-verified); post-RET head (FC00@44B1, zero exterior refs); interior out-calls call@44B2->0594 + call@44B4->2E2F; first link of 44B2-454
; ORIGIN 0x44B2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x2e2f
	ld     *(0x2f00),a
	and    #255,a
	stl    a,*(0x54d)
	ret
