; ROM6 0x85F6 SUB_85F6 -- 7w, symbols.yaml data_word.
; Evidence: Post-RET (ret 85F5 before); entry 108A F493 1A8B 6D8C 1C84 8084 (ALU lane, no calls); caller F074 @85F3 verified; first exit ret @85FC; bound 85F6-85FC; HYPOTHESIS.
; ORIGIN 0x85F6
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2-,a
	cmpl   a
	or     *ar3-,a
	mar    *ar4-
	xor    *ar4,a
	stl    a,*ar4
	ret
