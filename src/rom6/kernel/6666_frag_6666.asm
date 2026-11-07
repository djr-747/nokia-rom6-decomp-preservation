; ROM6 0x6666 FRAG_6666 -- 19w, symbols.yaml data_word.
; Evidence: Bound 6666-6678 (exit F073@6677->676A + operand); B-join entry 6655->6666 (post-exit head of FRAG_65AA); HYPOTHESIS.
; ORIGIN 0x6666
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    #6,b,a
	sub    *ar5,a
	bc     0x676a,agt
	stl    b,*ar5
	call   0x697f
	stm    #9751,ar1
	ld     *(0x53d),a
	stl    a,*ar1
	sub    #51,a
	bc     0x6672,ageq
	b      0x676a
