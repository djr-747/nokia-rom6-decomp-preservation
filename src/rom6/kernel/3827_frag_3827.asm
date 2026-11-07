; ROM6 0x3827 FRAG_3827 -- 7w, symbols.yaml data_word.
; Evidence: Bound 3827-382D (7w; exit B F073@382C->37DF + operand 382D, byte-verified; exit scan clean); entry bc F84D@381F->3827 byte-verified (chained from FRAG_381B interior); vestibule arm
; ORIGIN 0x3827
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,a
	and    #255,a
	stl    a,*(0x54d)
	b      0x37df
