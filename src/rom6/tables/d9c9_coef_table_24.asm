; ROM6 0xD9C9 D9C9_COEF_TABLE_24 -- 24w, symbols.yaml data_word.
; Evidence: Read-only coefficient table (24 words); loaded by mvpd 0xD9C9 block-moves at D9F7/DA13 into *AR2+ (math routine data). Recombine-clean.
; ORIGIN 0xD9C9
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0x0568
	.word 0x081D
	.word 0x0D5C
	.word 0x13F4
	.word 0x1A56
	.word 0x1FBA
	.word 0x2687
	.word 0x2B54
	.word 0x31AA
	.word 0x3585
	.word 0x0003
	.word 0x0004
	.word 0x0002
	.word 0x0002
	.word 0x0001
	.word 0x0002
	.word 0x0004
	.word 0x0024
	.word 0x0001
	.word 0x0001
	.word 0x0008
	.word 0x0028
	.word 0x0401
	.word 0x0200
