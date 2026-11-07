; ROM6 0x5C34 ROUTINE_5C34 -- 27w, symbols.yaml data_word.
; Evidence: Bound 5C34-5C4E (27w; exit RET FC00@5C4E byte-verified, exit scan clean); entries 8x calld F274@ 5C00/5C05/5C0D/5C12/5C1C/5C21/5C29/5C2E->5C34 byte-verified (all inside existing HU
; ORIGIN 0x5C34
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x674
	stm    #56,brc
	rptb   0x5c4d
	ld     a,-2,b
	stlm   b,ar3
	and    0x16,a
	ld     a,2,a
	neg    a
	stlm   a,t
	mar    *ar3+0
	ld     *ar3,ts,b
	and    0x61,b
	stl    b,*ar1(0x2f80)
	ld     0x11,a
	add    0x60,a
	sub    #456,a,b
	stlm   a,ar1
	ld     *ar5+,a
	add    0x17,a
	xc     1,bgt
	stlm   b,ar1
	ret
