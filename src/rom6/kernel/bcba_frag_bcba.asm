; ROM6 0xBCBA FRAG_BCBA -- 14w, symbols.yaml data_word.
; Evidence: Bound BCBA-BCC7 (14w; exit RET FC00@BCC7 byte-verified, exit scan clean); post-RET head only (FC00@BCB9 = FRAG_BCAC exit, zero exterior refs — 33CE-class thin entry); HYPOTHESIS.
; Pool: MASR/MACR rounded variants + || parallel pairs (all oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xBCBA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #13363,t
	rptbd  0xbcc6
	ld     *ar3,16,a
	masr   *ar4,a
	st     a,*ar4 || ld     *ar4,a
	macr   *ar4,a
	ld     *ar2,15,b
	sub    a,-1,b
	add    b,a
	st     a,*ar2+0% || ld     *ar5+0%,a
	st     b,*ar3+0% || masr   *ar4,a
	ret
