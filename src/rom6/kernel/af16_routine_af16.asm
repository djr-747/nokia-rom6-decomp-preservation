; ROM6 0xAF16 ROUTINE_AF16 -- 40w, symbols.yaml data_word.
; Evidence: Bound AF16-AF3D (38w; exit RET FC00@AF3D byte-verified, exit scan clean; interior join B@AF37-> AF3A); entries 3x call F074@B3AE/B3DF/B42E->AF16 byte-verified (all target head+2, n
; ORIGIN 0xAF16
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x3490),b
	and    #7,b
	stl    b,*(0x15)
	add    *(0x15),a
	stl    a,*(0x15)
	ld     *ar3+,b
	sub    #2,b
	stl    b,*(0x1a)
	mvdk   *ar5,0x12
	rptb   0xaf3c
	mvdk   *ar3+,0x14
	ld     *ar6,a
	sub    #1,a
	bc     0xaf3d,alt
	bc     0xaf39,aeq
	stl    a,*(0x11)
	rpt    *(0x11)
	mvdd   *ar4+,*ar2+
	b      0xaf3a
	mvdd   *ar4+,*ar2+
	mar    *ar6+
	nop
	nop
	ret
