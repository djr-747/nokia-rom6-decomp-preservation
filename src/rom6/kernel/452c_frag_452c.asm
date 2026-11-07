; ROM6 0x452C FRAG_452C -- 7w, symbols.yaml data_word.
; Evidence: Bound 452C-4532 (7w; exit B F073@4531->3028 + operand 4532 — branch-tailed); entry sibling-only B F073@451C->452C (from FRAG_44FD interior, chained entry) + pre-word 3028 (44FD exi
; ORIGIN 0x452C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #4,asm
	ld     #1,a
	ld     a,asm
	stl    a,*(0x537)
	b      0x3028
