; ROM6 0x65A5 FRAG_65A5 -- 5w, symbols.yaml data_word.
; Evidence: Bound 65A5-65A9 (5w; NO exit-class in-span — falls into FRAG_65AA head, no-exit micro-tail abut per 6753 precedent; pre-word 65AA = next-head value, not post-RET — entry is branch-
; ORIGIN 0x65A5
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1380,ar2
	xc     2,aeq
	addm   #8,*ar2
