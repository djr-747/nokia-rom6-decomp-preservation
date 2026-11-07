; ROM6 0x3A8E FRAG_3A8E -- 40w, symbols.yaml data_word.
; Evidence: Bound 3A8E-3AB5 (40w; exit RET FC00@3AB5 byte-verified, exit scan clean); entries bc F84D@3A87-> 3A8E byte-verified (from ROUTINE_3A81 [3A81-3A8D] tail, chained edge) + post-RET he
; ORIGIN 0x3A8E
	.sect ".text"
	.mmregs
	.global _start
_start:
	portr  58,*(0xb)
	and    #255,b
	neg    b
	add    #212,b
	sfta   b,-4,a
	and    #15,a
	add    *(0x12),a
	stlm   a,ar2
	and    #15,b
	portr  59,*(0x8)
	and    #4095,a
	neg    b
	stm    #14,brc
	rptb   0x3aad
	xc     1,blt
	sfta   a,1
	add    #1,b
	nop
	nop
	ld     *ar2+,b
	mvdk   *ar2,0xc
	xor    b,a
	sth    a,*ar2-
	stl    a,*ar2
	ld     #64,a
	ret
