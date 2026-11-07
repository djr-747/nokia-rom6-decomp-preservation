; ROM6 0xAFB5 TABLE_AFB5 -- 10w, symbols.yaml data_word.
; Evidence: Bound AFB5-AFBE (10w bacc-dispatch table of DISPATCH_AFAB; bytes verified: AFBF/AFD3/AFF9/B017/B04B/B050/B062/B080/B0BD/B0C2 — AFD3 not AFF3); HYPOTHESIS table.
; ORIGIN 0xAFB5
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0xAFBF
	.word 0xAFD3
	.word 0xAFF9
	.word 0xB017
	.word 0xB04B
	.word 0xB050
	.word 0xB062
	.word 0xB080
	.word 0xB0BD
	.word 0xB0C2
