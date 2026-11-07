; ROM6 0x9A37 FRAG_9A37 -- 25w, symbols.yaml data_word.
; Evidence: Bound 9A37-9A4F (25w; exit retd FE00@9A4D + delays 9A4E-9A4F byte-verified); entry F830@9A1E cond- branch (in-dump, byte-verified); interior F072@9A3C->9A41 + F808@9A43->9A4C joins
; Pool: RPTB loop grows A <<=16 per pass with BRC = entry-A-low (unbound) -- 40-bit accumulator growth has no exact 32-bit long form; STH_SHIFT (6FD3 0C98, store HIGH of A arith>>8) per the 8433 precedent; carry-branch (bc nc) computable but blocked by the 40-bit growth. stays .asm, bytes verified.
; ORIGIN 0x9A37
	.sect ".text"
	.mmregs
	.global _start
_start:
	stlm   a,brc
	ld     *ar3,8,a
	and    #255,16,a
	rptb   0x9a41
	or     *ar2+,a
	stl    a,-8,*ar3+%
	sftl   a,8
	sftl   a,8
	sftl   b,-1
	bc     0x9a4c,nc
	ssbx   st1,intm
	andm   #-4097,*(0x20ff)
	reted
	mvmd   ar3,0x21fc
	mar    *ar3-%
	retd
	mvmd   ar3,0x21fc
