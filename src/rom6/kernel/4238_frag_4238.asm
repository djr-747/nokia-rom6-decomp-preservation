; ROM6 0x4238 FRAG_4238 -- 3w, symbols.yaml data_word.
; Evidence: Bound 4238-423A (3w micro: RETD FE00@4238 + delays 4239-423A (mvdd 2w), byte-verified; exit scan clean); entry bcd FA30@4233->4238 byte-verified (cond tc, exterior from SWEEP_PROC_
; ORIGIN 0x4238
	.sect ".text"
	.mmregs
	.global _start
_start:
	retd
	mvdd   *ar3-,*ar2-
	mvdd   *ar3,*ar2
