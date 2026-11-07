; ROM6 0x85E4 BLOCK_COPY_85E4 -- 18w, symbols.yaml data_word.
; Evidence: Entry E743 7712 30D0 EC05 E598 EC05; first exit ret FC00 @85F5 (rpt/mvdd loop, interior call 85F6 @85F3); caller F074 @8547 verified; HYPOTHESIS.
; ORIGIN 0x85E4
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmm   ar4,ar3
	stm    #12496,ar2
	rpt    #5
	mvdd   *ar3+,*ar2+
	rpt    #5
	mvdd   *ar4+,*ar2+
	stm    #12505,ar2
	stm    #12503,ar3
	stm    #5,brc
	rptb   0x85f4
	call   0x85f6
	ret
