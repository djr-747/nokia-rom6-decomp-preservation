; ROM6 0x4B06 FRAG_4B06 -- 38w, symbols.yaml data_word.
; Evidence: Bound 4B06-4B2B (38w; exit RET FC00@4B2B byte-verified, exit scan clean); entries bc F820@4AF8-> 4B07 byte-verified (exterior, SUB_4AF3 span) + F84D@4B00->4B06 (gap-interior pre-he
; ORIGIN 0x4B06
	.sect ".text"
	.mmregs
	.global _start
_start:
	rsbx   st1,intm
	addm   #7,*(0x13)
	stm    #12032,ar4
	stm    #3,brc
	rptb   0x4b14
	ld     *ar3(0x1),16,a
	or     *ar3+,a
	sfta   a,-2
	stl    a,*ar4+
	and    #511,a
	ld     *ar3(0xffff),b
	and    #-2048,b
	add    b,a
	stl    a,*ar4(0xffff)
	rpt    #3
	mvdd   *ar3+,*ar4+
	stm    #12032,ar4
	mvdk   *ar2,0x13
	stm    #7,brc
	rptb   0x4b2a
	ld     *ar4+,a
	xor    *ar3,a
	stl    a,*ar3+
	ret
