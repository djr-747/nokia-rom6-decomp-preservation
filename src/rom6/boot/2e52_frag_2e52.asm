; ROM6 0x2E52 FRAG_2E52 -- 18w, symbols.yaml data_word.
; Evidence: Bound 2E52-2E63 (18w; exit RET FC00@2E63 byte-verified, exit scan clean); post-RET head only (FC00@2E51, zero exterior callers/branchers — thin entry per 3267 precedent); interior 
; ORIGIN 0x2E52
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x37d8
	bitf   *(0x866),#3
	rc     ntc
	bitf   *(0x2628),#16384
	bc     0x2e61,ntc
	bitf   *(0x250f),#208
	rc     tc
	call   0x2e64
	ret
