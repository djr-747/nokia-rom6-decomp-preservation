; ROM6 0x3460 DISPATCH_CMP_3460 -- 21w, symbols.yaml data_word.
; Evidence: Entry F0F8/F030/00FF/8813 (sftl a,-8; and #255; stlm ar3) + cmpm *(0x250F),#34 + bc 3475/3480; Bound 345B-345F + 3460-3474 (head annex: TRACE proves 345B/5D/5E/5F execute x9 in 821
; ORIGIN 0x3460
	.sect ".text"
	.mmregs
	.global _start
_start:
	sftl   a,-8
	and    #255,a
	stlm   a,ar3
	cmpm   *(0x250f),#34
	sub    #112,b,a
	bc     0x3475,aeq
	sub    #176,b,a
	bc     0x3480,aeq
	sub    #177,b,a
	bc     0x3491,aeq
	b      0x3497
