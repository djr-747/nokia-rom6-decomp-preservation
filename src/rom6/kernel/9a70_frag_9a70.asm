; ROM6 0x9A70 FRAG_9A70 -- 18w, symbols.yaml data_word.
; Evidence: Bound 9A70-9A81 (18w; NO own unconditional exit: ends cond-return rc FC43@9A81 + falls into FRAG_9A82 head — tail-frag abut, not a routine); entries bc F820@9A5D->9A70 byte-verifie
; ORIGIN 0x9A70
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x2510),a
	and    #240,a
	sub    #208,a
	bc     0x9a82,aneq
	ldu    *(0x20fa),a
	sub    #2,a
	bc     0x9a82,ageq
	ld     *ar3,a
	sub    #50,a
	rc     alt
