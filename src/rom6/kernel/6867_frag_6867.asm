; ROM6 0x6867 FRAG_6867 -- 10w, symbols.yaml data_word.
; Evidence: Bound 6867-6870 (10w; exit RET FC00@6870 byte-verified, first and only unconditional exit-class; exit scan clean); entries 2x bc F84x@67A2/6853->6867 byte-verified (both aleq, exte
; ORIGIN 0x6867
	.sect ".text"
	.mmregs
	.global _start
_start:
	portr  3,*(0x8)
	and    #256,a
	rc     aneq
	orm    #128,*(0x263a)
	ret
