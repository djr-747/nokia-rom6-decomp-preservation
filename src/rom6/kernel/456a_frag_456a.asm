; ROM6 0x456A FRAG_456A -- 14w, symbols.yaml data_word.
; Evidence: Bound 456A-4577 (14w; exit RET FC00@4577 byte-verified, exit scan clean); post-RET head (FC00@4569, CODE cell); zero exterior refs — thin entry per 3AB6 precedent; HYPOTHESIS.
; ORIGIN 0x456A
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	sub    #1274,b
	bc     0x4576,bgt
	ldm    ar3,b
	sub    #1263,b
	bc     0x4576,blt
	stm    #12132,ar3
	mvdd   *ar3+,*ar4+
	ret
