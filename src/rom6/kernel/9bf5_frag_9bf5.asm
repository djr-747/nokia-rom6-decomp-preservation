; ROM6 0x9BF5 FRAG_9BF5 -- 3w, symbols.yaml data_word.
; Evidence: Bound 9BF5-9BF7 (3w; exit B F073@9BF6->9C15 + operand 9BF7 — branch-tailed into FRAG_9C13 zone; micro-span, entry+exit verified); entry bc F845@9BED->9BF5 byte-verified (from FRAG_
; ORIGIN 0x9BF5
	.sect ".text"
	.mmregs
	.global _start
_start:
	mar    *ar7+
	b      0x9c15
