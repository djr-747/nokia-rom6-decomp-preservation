; ROM6 0xB050 FRAG_B050 -- 18w, symbols.yaml data_word.
; Evidence: Bound B050-B061 (18w, exit FC00@B061); post-RET head (after FC00@B04F); interior rc+cc conditional returns, passed through; HYPOTHESIS.
; ORIGIN 0xB050
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67a
	call   0xa2c3
	call   0xa361
	rc     aneq
	call   0xa4de
	call   0xa482
	cc     0xa815,aneq
	calld  0xa2b9
	stm    #-8721,ar5
	ret
