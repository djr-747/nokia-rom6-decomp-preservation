; ROM6 0xE9D6 ZERO_24 -- 24w, symbols.yaml data_word.
; Evidence: 24 zero words E9D6-E9ED (objdump collapses to ...; image bytes verified zero); padding between fbacc tail (E9D5) and E9EE pairedword table; no refs, no intent. Recombine-clean.
; ORIGIN 0xE9D6
	.sect ".text"
	.mmregs
	.global _start
_start:
; FORM .word (zero padding)
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
	.word 0x0000
