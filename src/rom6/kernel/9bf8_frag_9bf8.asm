; ROM6 0x9BF8 FRAG_9BF8 -- 27w, symbols.yaml data_word.
; Evidence: Bound 9BF8-9C12 (27w; exit B F073@9C11->9C15 + operand 9C12 — branch-tailed into FRAG_9C13 zone; exit scan otherwise clean); entries bc F845@9BF1->9BF8 byte-verified (from FRAG_9BC
; ORIGIN 0x9BF8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar6,a
	sub    *(0x20fe),a
	bc     0x9c15,aeq
	banz   0x9c07,*ar4
	ld     *ar2,-8,b
	mar    *ar4+
	mar    *ar6+
	bd     0x9c0c
	and    #255,b
	ld     *ar2+%,b
	mar    *ar4-
	mar    *ar6+
	and    #255,b
	xor    #193,b,a
	bc     0x9c13,aneq
	mar    *ar7+
	b      0x9c15
