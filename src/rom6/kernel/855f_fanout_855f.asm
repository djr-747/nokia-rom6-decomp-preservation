; ROM6 0x855F FANOUT_855F -- 19w, symbols.yaml data_word.
; Evidence: Entry E742 E753 F074 8572 1086 F074; first exit ret FC00 @8571; callers F074 @8541/8550 verified; interior calls to 8572/8577/8588/85AD/85E4 region; HYPOTHESIS.
; ORIGIN 0x855F
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar4,ar2
	mvmm   ar5,ar3
	call   0x8572
	ld     *ar6,a
	call   0x8573
	call   0x8572
	call   0x8572
	ld     *ar6,a
	call   0x8573
	call   0x8572
	call   0x8588
	ret
