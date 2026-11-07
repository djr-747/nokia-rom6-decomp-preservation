; ROM6 0x614F FRAG_614F -- 6w, symbols.yaml data_word.
; Evidence: Entry 6181 0001 (bitf *ar1,#1); bound 614F-6154 (first exit retd @6152 +delays); zero interior calls; inbound bc @60B2 (F830 tc) + post-retd 614C+2; HYPOTHESIS.
; ORIGIN 0x614F
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar1,#1
	rc     ntc
	retd
	st     #64,*ar5
