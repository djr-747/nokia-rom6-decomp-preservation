; ROM6 0x44FD FRAG_44FD -- 47w, symbols.yaml data_word.
; Evidence: Bound 44FD-452B (47w; exit B F073@452A->3028 + operand 452B — branch-tailed outside gap; exit scan otherwise clean); post-RET head (FC00@44FC); interior out-calls call@44FD->0594 +
; ORIGIN 0x44FD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	ld     *(0x2f00),a
	and    #255,a
	pshm   al
	pshm   ah
	pshm   ag
	call   0x2e2f
	ld     *(0x871),a
	sub    #0,a,b
	bc     0x4511,beq
	stlm   a,ar2
	call   0x226c
	popm   ag
	popm   ah
	popm   al
	bc     0x451e,aneq
	calld  0x2262
	stm    #13,ar2
	call   0x226c
	b      0x452c
	calld  0x2262
	stm    #14,ar2
	call   0x226c
	calld  0x2262
	stm    #4,ar2
	call   0x226c
	b      0x3028
