; ROM6 0x8588 BLOCK_COPY_8588 -- 37w, symbols.yaml data_word.
; Evidence: Entry E742 EC05 7192 30D0 7712 30D9; first exit ret FC00 @85AC (mvmm/rpt/mvdk/mvkd copy loop); callers F074 @8557/856F verified; HYPOTHESIS.
; ORIGIN 0x8588
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar4,ar2
	rpt    #5
	mvdk   *ar2+,0x30d0
	stm    #12505,ar2
	mvkd   0x14,*ar2-
	st     #12500,*ar2-
	st     #12498,*ar2-
	st     #12496,*ar2
	call   0x85ad
	addm   #2,*ar2-
	st     #12496,*ar2-
	st     #12500,*ar2-
	st     #12498,*ar2
	call   0x85ad
	addm   #2,*ar2-
	st     #12498,*ar2-
	st     #12496,*ar2-
	st     #12500,*ar2
	call   0x85ad
	ret
