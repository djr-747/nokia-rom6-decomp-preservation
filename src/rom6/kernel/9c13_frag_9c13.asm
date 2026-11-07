; ROM6 0x9C13 FRAG_9C13 -- 58w, symbols.yaml data_word.
; Evidence: Bound 9C13-9C4C (exit FC00@9C4C); entries bc@9C0E->9C13 (byte-verified) + 4x joins@9C15; interior F073@9C2B->9C35 verified interior join (parent census) — span STANDS (critic kill 
; ORIGIN 0x9C13
	.sect ".text"
	.mmregs
	.global _start
_start:
	xor    #32,b
	ld     b,a
	ldm    ar7,b
	cc     0x9b5c,beq
	ldm    ar6,a
	sub    *(0x20fe),a
	bc     0x9c21,aeq
	ldm    ar7,a
	bc     0x9bdc,aeq
	call   0x9c4d
	mar    *ar5-
	mar    *ar5-
	banz   0x9c2d,*ar3
	mar    *ar1-
	ldu    *ar1+,a
	sftl   a,8
	or     a,-16
	b      0x9c35
	mar    *ar1-
	ld     *ar1+,a
	and    #255,a
	ld     *ar1+,b
	and    #-256,b
	or     b,a
	mvmm   ar5,ar6
	pshm   al
	calld  0x9c61
	stm    #12032,ar2
	ld     #0,b
	popm   bl
	nop
	xor    b,a
	stm    #12032,ar3
	ccd    0x2c88,aeq
	stm    #155,ar4
	ld     *(0x20fe),a
	sub    #4,a
	st     #-1,*(0x20fa)
	ret
