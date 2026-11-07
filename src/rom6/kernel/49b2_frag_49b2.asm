; ROM6 0x49B2 FRAG_49B2 -- 4w, symbols.yaml data_word.
; Evidence: Bound 49B2-49B5 (4w incl operand; exit B F073@49B4->4AD8 + operand 49B5 byte-verified — NOTE corrects earlier ->49B6 misread: w[49B5]=4AD8, not 49B6; 4AD8 dark/unclaimed, dispositi
; ORIGIN 0x49B2
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    b,*(0x2656)
	b      0x4ad8
