; ROM6 0x3850 FRAG_3850 -- 18w, symbols.yaml data_word.
; Evidence: Bound 3850-3861 (18w; exit B F073@3860->37DF + operand 3861, byte-verified; exit scan clean); entries 3x B F073@3842/3847/384E->3850 byte-verified (chained hub entries); vestibule 
; ORIGIN 0x3850
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar4,a
	and    #255,a
	ldm    ar3,b
	sftl   b,8
	or     a,b
	stlm   b,ar0
	ldm    ar3,a
	and    #-256,a
	ldm    ar4,b
	sftl   b,-8
	or     b,a
	ld     #2,b
	call   0x93ce
	b      0x37df
