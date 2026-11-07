; ROM6 0xAEAD DATA_TABLE_44 -- 44w, symbols.yaml data_word.
; Evidence: 44 words AEAD-AED8 headed 000F 000B 0008 000C 000E 0009 (bytes verified); READA-consumed by AD0D driver (ld #AEAD @AD20, reada *ar2 @AD26); AR5 sub-range walks observed. Bound AEAD
; ORIGIN 0xAEAD
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0x000F
	.word 0x000B
	.word 0x0008
	.word 0x000C
	.word 0x000E
	.word 0x0009
	.word 0x07D0
	.word 0x0834
	.word 0x0898
	.word 0x08FC
	.word 0x0960
	.word 0x04E2
	.word 0x0686
	.word 0x09D8
	.word 0x0C62
	.word 0x109A
	.word 0x0753
	.word 0x08F7
	.word 0x0C49
	.word 0x0C62
	.word 0x109A
	.word 0x04E2
	.word 0x0686
	.word 0x0C49
	.word 0x0C62
	.word 0x109A
	.word 0x04C1
	.word 0x04E9
	.word 0x0CB2
	.word 0x0CE4
	.word 0x1068
	.word 0x109A
	.word 0x0732
	.word 0x075A
	.word 0x0CB2
	.word 0x0CE4
	.word 0x1068
	.word 0x109A
	.word 0x02D5
	.word 0x02EE
	.word 0x0A28
	.word 0x0A41
	.word 0x0FF0
	.word 0x1009
