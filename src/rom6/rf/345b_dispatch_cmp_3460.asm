; ROM6 0x345B DISPATCH_CMP_3460 -- 5w, symbols.yaml data_word.
; Evidence: Entry F0F8/F030/00FF/8813 (sftl a,-8; and #255; stlm ar3) + cmpm *(0x250F),#34 + bc 3475/3480; Bound 345B-345F + 3460-3474 (head annex: TRACE proves 345B/5D/5E/5F execute x9 in 821
; ORIGIN 0x345B
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1,ar0
	ld     *ar2,a
	and    #255,a,b
