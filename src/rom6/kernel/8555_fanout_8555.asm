; ROM6 0x8555 FANOUT_8555 -- 10w, symbols.yaml data_word.
; Evidence: Entry 4A14 E754 F074 8588 F074 85FD; first exit ret FC00 @855E; callers F074 @8510/8511?/8531 verified (@8510/@851B/@8531); HYPOTHESIS.
; ORIGIN 0x8555
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar4
	mvmm   ar5,ar4
	call   0x8588
	call   0x85fd
	popm   ar4
	call   0x853b
	ret
