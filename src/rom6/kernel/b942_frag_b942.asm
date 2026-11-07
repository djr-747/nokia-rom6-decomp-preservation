; ROM6 0xB942 FRAG_B942 -- 6w, symbols.yaml data_word.
; Evidence: Bound B942-B947 (6w; exit F073@B946->B8B0 + operand B947, byte-verified); post-RET head; head calld F274@B942->B743 (out-call as head word); zero callers; joins B->B9D9 x2 + BD->B9
; ORIGIN 0xB942
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xb743
	stm    #12206,ar3
	b      0xb8b0
