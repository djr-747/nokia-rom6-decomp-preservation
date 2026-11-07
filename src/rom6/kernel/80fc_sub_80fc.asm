; ROM6 0x80FC SUB_80FC -- 14w, symbols.yaml data_word.
; Evidence: Entry F074 059E 8815 F274 2282 7712; zero callers (4x bc NOT counted); interior calld existing 0x7C9E @8105; first exit ret @8109 (abuts 810A); bound 80FC-8109; HYPOTHESIS.
; ORIGIN 0x80FC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stlm   a,ar5
	calld  0x2282
	stm    #5,ar2
	bc     0x6f8,tc
	calld  0x7c9e
	stm    #9807,ar2
	ret
