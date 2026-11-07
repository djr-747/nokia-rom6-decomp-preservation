; ROM6 0x9B63 FRAG_9B63 -- 4w, symbols.yaml data_word.
; Evidence: Bound 9B63-9B66 (4w micro: or + RETD FE00@9B64 + delays 9B65-9B66, byte-verified; exit scan clean); entry = fall-through abut from MSG_LEAF_9B5C [9B5C-9B62] tail (CODE, ends stl-in
; ORIGIN 0x9B63
	.sect ".text"
	.mmregs
	.global _start
_start:
	or     *ar1,a
	retd
	mar    *ar3-
	stl    a,*ar1+
