; ROM6 0xB177 TABLE_B177 -- 6w, symbols.yaml data_word.
; Evidence: Bound B177-B17C (6w bacc-dispatch table of DISPATCH_B16C; bytes verified: B17D/B1ED/B21F/B26E/B308/B346); HYPOTHESIS table.
; ORIGIN 0xB177
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0xB17D
	.word 0xB1ED
	.word 0xB21F
	.word 0xB26E
	.word 0xB308
	.word 0xB346
