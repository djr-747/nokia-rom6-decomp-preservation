; ROM6 0x3623 FRAG_3623 -- 29w, symbols.yaml data_word.
; Evidence: Bound 3623-363F (29w; exit B F073@363E->2E64 + operand 363F, byte-verified; exit scan clean); entry bc F820@361F->3623 byte-verified (cond ntc, exterior from FRAG_361C [361C-3622] 
; ORIGIN 0x3623
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdk   *ar2+%,0x15
	mvdk   *ar2+%,0x10
	ldu    *ar2+%,b
	stlm   b,ar4
	add    #1,b,a
	sftl   a,-1
	sub    #1,a
	stlm   a,brc
	stm    #12032,ar3
	rptb   0x3634
	ldu    *ar2+%,a
	stl    a,*ar3+
	mar    *ar2-%
	call   0x2e2f
	ldm    ar4,b
	ldm    ar5,a
	calld  0x93ce
	stm    #12032,ar2
	b      0x2e64
