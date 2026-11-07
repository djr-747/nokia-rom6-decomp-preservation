; ROM6 0xAE6C JUMP_TABLE_4 -- 4w, symbols.yaml data_word.
; Evidence: 4 table words AE70 AE71 AE75 AE79 @AE6C-AE6F (bytes verified) between RET@AE6B and RET@AE70; consumer add #AE6C @ADDA + reada @ADDE + cala b @ADE0 (routine 0xAD0D driver); target r
; ORIGIN 0xAE6C
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0xAE70
	.word 0xAE71
	.word 0xAE75
	.word 0xAE79
