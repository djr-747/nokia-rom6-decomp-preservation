; ROM6 0x388C FRAG_388C -- 16w, symbols.yaml data_word.
; Evidence: Bound 388C-389B (16w; exit F073@389A->38AA + operand 389B — forward join into sibling FRAG_389C span, byte-verified); entries 2x B F073@AE73/AE77->388C byte-verified (far uncond re
; ORIGIN 0x388C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x62a
	bitf   *(0x3ec8),#2
	bc     0x3938,tc
	bitf   *(0x51f),#128
	bc     0x3907,tc
	ld     *(0x3e7f),b
	b      0x38aa
