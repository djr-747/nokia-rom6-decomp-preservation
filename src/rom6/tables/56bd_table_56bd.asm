; ROM6 0x56BD TABLE_56BD -- 33w, symbols.yaml data_word.
; Evidence: Bound 56BD-56DD (33w data table; zero F07x/F4Ex code words, no calls/branches/RET; LD #56xx immediates in J6 are values not pointers); semantics open (candidate threshold/coeff wor
; ORIGIN 0x56BD
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (data table)
	.word 0x2A39
	.word 0x2E3D
	.word 0x5D06
	.word 0x610A
	.word 0x202F
	.word 0x2433
	.word 0x2837
	.word 0x2C3B
	.word 0x5362
	.word 0x5700
	.word 0x5B04
	.word 0x5F08
	.word 0x06FF
	.word 0x0CFF
	.word 0x10FF
	.word 0x16FF
	.word 0x1AFF
	.word 0x20FF
	.word 0x24FF
	.word 0x2AFF
	.word 0x2EFF
	.word 0x1625
	.word 0x1A29
	.word 0x202F
	.word 0x2400
	.word 0x000F
	.word 0x0413
	.word 0x0817
	.word 0x0C1B
	.word 0x101F
	.word 0x1423
	.word 0x1827
	.word 0x1C2B
