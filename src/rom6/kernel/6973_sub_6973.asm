; ROM6 0x6973 SUB_6973 -- 12w, symbols.yaml data_word.
; Evidence: Bound 6973-697E (exit FC00@697E); callers F274@642A (ext calld) + F074@6962 (internal forward from SUB_6961); interior join F073@6974->6978 (tail-merge, kept in-span); HYPOTHESIS.
; ORIGIN 0x6973
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     b,a
	b      0x6978
	sub    #1,a,b
	add    *ar1,b
	sub    *ar2,b
	sub    a,b
	bc     0x697a,bgeq
	add    a,b
	ret
