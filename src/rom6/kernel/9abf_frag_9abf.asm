; ROM6 0x9ABF FRAG_9ABF -- 19w, symbols.yaml data_word.
; Evidence: Bound 9ABF-9AD1 (19w; exit B F073@9ACB->9AD2 + operand 9AD2 — chained into FRAG_9AD2 head per 4C41/4CB4 precedent; exit scan otherwise clean; pre-word 9AD2 = next-head address, not
; Pool: BCD on carry flag (carry unbound) + RPTBD lane; stays .asm, bytes verified.
; ORIGIN 0x9ABF
	.sect ".text"
	.mmregs
	.global _start
_start:
	sfta   b,-1
	bcd    0x9acd,nc
	stm    #1,ar0
	orm    #-32768,*(0x20ff)
	rpt    *(0xb)
	mvdd   *ar2+0%,*ar3+
	mar    *ar2-%
	b      0x9ad2
	sub    #1,b
	rpt    *(0xb)
	mvdd   *ar2+0%,*ar3+
