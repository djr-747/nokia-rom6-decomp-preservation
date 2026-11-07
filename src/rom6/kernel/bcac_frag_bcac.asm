; ROM6 0xBCAC FRAG_BCAC -- 14w, symbols.yaml data_word.
; Evidence: Bound BCAC-BCB9 (14w; exit RET FC00@BCB9 byte-verified, exit scan clean); post-RET head only (FC00@BCAB, zero ext refs — thin entry); interior F072@BCAD->BCB8 (rptb per objdump, fa
; Pool: MASR/MACR rounded variants + || parallel pairs (oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xBCAC
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar3,16,a
	rptb   0xbcb8
	masr   *ar5+,*ar4,a
	st     a,*ar4 || ld     *ar4,b
	ld     *ar2,a || macr   *ar4+,b
	masr   *ar5-,*ar4,a
	st     a,*ar4 || ld     *ar4,a
	st     b,*ar2 || macr   *ar4-,a
	sfta   a,-1
	sub    b,-1,a
	st     a,*ar3+0% || add    *ar2,b
	st     b,*ar2+0% || ld     *ar3,a
	ret
