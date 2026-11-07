; ROM6 0x89EB FRAG_89EB -- 9w, symbols.yaml data_word.
; Evidence: Bound 89EB-89F3 (entry banz 6C8D@89E8->89EB byte-verified; exit bd F273@89F0->89D2 + slots 89F2-89F3); interior bc@89EC->89CE; merges into ROUTINE_89C4 span (89D2 inside); HYPOTHES
; ORIGIN 0x89EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	bc     0x89ce,bneq
	stm    #1,ar3
	bd     0x89d2
	stm    #120,t
