; ROM6 0xB129 TABLE_B129 -- 6w, symbols.yaml data_word.
; Evidence: Bound B129-B12E (6w bacc-dispatch table of DISPATCH_B11C; bytes verified: B12F/B141/B146/B14B/B157/B15C); HYPOTHESIS table.
; ORIGIN 0xB129
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0xB12F
	.word 0xB141
	.word 0xB146
	.word 0xB14B
	.word 0xB157
	.word 0xB15C
