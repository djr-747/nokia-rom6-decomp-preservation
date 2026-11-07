; ROM6 0x649D FRAG_649D -- 2w, symbols.yaml data_word.
; Evidence: Bound 649D-649E (2w micro: stl + exit B F073@649E->676A + operand 649F (shared with SUB85_644B head per 8AA5 precedent), byte-verified; 676A = BRANCH_TAIL_676A head, CODE; exit sca
; ORIGIN 0x649D
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    b,*ar5
	b      0x676a
