; ROM6 0xE38A BLK_E38A -- 11w, symbols.yaml data_word.
; Evidence: Post-RET head; BOUND CORRECTED entry-linear: straight-line to first exit retd @0xE392, bound E38A-E394 (incl delay); was E42C (overclaim); no callers listed; HYPOTHESIS.
; Pool: MPYR round-multiply + parallel || dual op (both oracle-unbound); stays .asm, bytes verified.
; ORIGIN 0xE38A
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8,brc
	rptbd  0xe391
	mvdd   *ar2+,*ar4+
	ld     *ar3+,t
	mpyr   *ar2+,a
	st     a,*ar4+ || ld     *ar3+,t
	retd
	mpyr   *ar2+,a
	sth    a,*ar4+
