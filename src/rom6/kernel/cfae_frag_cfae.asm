; ROM6 0xCFAE FRAG_CFAE -- 15w, symbols.yaml data_word.
; Evidence: Bound CFAE-CFBC (15w; exit RET FC00@CFBC byte-verified, exit scan clean); post-RET head only (FC00@CFAD); no joins; HYPOTHESIS.
; ORIGIN 0xCFAE
	.sect ".text"
	.mmregs
	.global _start
_start:
	rpt    #43
	mvkd   0xf10,*ar2+
	stm    #3170,ar2
	stm    #3180,ar3
	rpt    #9
	mvkd   0xf7e,*ar2+
	rpt    #9
	mvkd   0xf7e,*ar3+
	popm   st1
	ret
