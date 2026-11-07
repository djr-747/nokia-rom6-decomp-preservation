; ROM6 0xC7E9 FRAG_C7E9 -- 13w, symbols.yaml data_word.
; Evidence: Bound C7E9-C7F5 (13w; exit F073@C7F4->283D + operand C7F5, single exit-class word in span, byte- verified); sole entry bc F830@C7D4->C7E9 byte-verified (cond, from FRAG_C7B1 interi
; ORIGIN 0xC7E9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*ar6
	ld     *ar5,b
	and    #-14848,b
	and    #-14848,a
	sub    a,b
	bc     0xc7f8,beq
	andm   #-1537,*ar6
	b      0x283d
