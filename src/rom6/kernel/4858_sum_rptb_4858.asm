; ROM6 0x4858 SUM_RPTB_4858 -- 43w, symbols.yaml data_word.
; Evidence: Entry F074 059E + ldm ar5 + add #36 + add *ar2+ RPTB-4865 accumulation; first-RET FC00 @0x4882; 1 caller 0x467A via F074 (objdump call 0x4858 verified); HYPOTHESIS sum loop.
; ORIGIN 0x4858
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	ldm    ar5,b
	add    #36,b
	stlm   b,ar2
	ld     #0,a
	ld     #0,b
	stm    #43,brc
	rptb   0x4865
	add    *ar2+,a
	add    *ar2+,b
	stm    #502,ar2
	stm    #500,ar3
	pshm   bl
	pshm   bh
	pshm   bg
	ld     #1,b
	xc     1,alt
	neg    b
	add    *ar2,b
	stl    b,*ar2+
	popm   ag
	popm   ah
	popm   al
	add    #8,b
	stl    b,-4,*ar3+
	ld     #1,b
	xc     1,alt
	neg    b
	add    *ar2,b
	stl    b,*ar2
	add    #8,b
	stl    b,-4,*ar3
	ret
