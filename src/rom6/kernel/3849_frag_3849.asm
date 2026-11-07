; ROM6 0x3849 FRAG_3849 -- 7w, symbols.yaml data_word.
; Evidence: Bound 3849-384F (7w; exit B F073@384E->3850 + operand 384F, byte-verified; exit scan clean); entry bc F84D@383B->3849 byte-verified (chained from FRAG_382E interior); hub-feeder ar
; ORIGIN 0x3849
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #3100,*(0x2202)
	call   0xc851
	b      0x3850
