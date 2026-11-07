; ROM6 0xE0B5 ROUTINE_E0B5 -- 56w, symbols.yaml data_word.
; Evidence: Bound E0B5-E0EC (56w; exit RET FC00@E0EC byte-verified, exit scan clean); entries 2x calld F274@ D173/D825->E0B5 byte-verified head-exact (call-only entry, pre-word B4AF = retd del
; ORIGIN 0xE0B5
	.sect ".text"
	.mmregs
	.global _start
_start:
	neg    a
	ld     #6,b
	mvmm   ar2,ar6
	mar    *ar2-0
	stm    #5,t
	xc     2,alt
	add    b,a
	mar    *ar2-
	sub    a,b
	stl    a,0x7b
	ld     #1,a
	mac    0x7b,a
	add    0x13,a
	stlm   a,ar4
	stl    b,0x7b
	sub    #6,b,a
	ld     #1,b
	mac    0x7b,b
	xc     2,aeq
	ld     #1,b
	mar    *ar4-
	add    0x13,b
	stlm   b,ar5
	stm    #39,brc
	stm    #-9,ar0
	rptbd  0xe0eb
	mvmm   ar2,ar3
	mar    *ar2-
	mpy    *ar3+,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2-,*ar4+,a
	mac    *ar3+,*ar5+,a
	mac    *ar2,*ar4+0%,a
	macr   *ar3+0%,*ar5+0%,a
	mar    *ar2-0%
	sth    a,*ar6+
	ret
