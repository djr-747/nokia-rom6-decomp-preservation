; ROM6 0xA8B9 FRAG_A8B9 -- 6w, symbols.yaml data_word.
; Evidence: Bound A8B9-A8BE (6w; exit RET FC00@A8BE byte-verified, exit scan clean; micro-span); entry B F073@ AE4->A8B9 byte-verified (from block01 uploaded code); pre-word FC45 not post-RET 
; ORIGIN 0xA8B9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9593,ar2
	ld     #0,a
	rpt    #8
	stl    a,*ar2+
	ret
