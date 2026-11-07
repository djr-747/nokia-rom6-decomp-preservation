; ROM6 0xAF64 JTAB_AF57_6WAY -- 6w, symbols.yaml data_word.
; Evidence: 6 words AF6A/AF74/AF79/AF7E/AF83/AF88 @AF64-AF69 (bytes verified); each handler head with ret exit (calld 0xa2b9 lanes objdump-verified); consumer is AF57 bacc dispatch. Bound AF64
; ORIGIN 0xAF64
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0xAF6A
	.word 0xAF74
	.word 0xAF79
	.word 0xAF7E
	.word 0xAF83
	.word 0xAF88
