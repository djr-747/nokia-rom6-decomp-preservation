; ROM6 0xC556 FRAG_C556 -- 32w, symbols.yaml data_word.
; Evidence: Bound C556-C575 (32w; exit RET FC00@C575 byte-verified, exit scan clean); post-RET head only (FC00@C555, zero ext refs); head RPTB-form 7716 0008 / F272 C574; remainder C576-C5C2 (
; ORIGIN 0xC556
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8,ar6
	rptbd  0xc574
	stm    #12,ar7
	ld     *ar4,15,a
	mac    *ar3,*ar2,a
	mvdd   *ar2,*ar4-
	sfta   a,-2
	ld     #0,b
	macsu  *ar4-,*ar3,b
	sub    b,-16,a
	mas    *ar4,*ar3,a
	sfta   a,1
	st     a,*ar4+ || ld     *ar5+,t
	stl    a,*ar4+
	sub    *ar2,14,a,b
	add    *ar2,14,a
	sfta   a,-4
	mas    *ar7-,a
	mpyu   *ar7+,b
	sub    b,-16,a
	ld     #64,b
	maca   *ar5-,b
	sfta   b,9
	mpyu   *ar6,a
	add    a,-7,b
	sat    b
	sth    b,*ar2+
	ret
