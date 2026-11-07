; ROM6 0x73EB MAC_DIV_ENGINE_2F05 -- 79w, symbols.yaml data_word.
; Evidence: Entry F074 0596; bound 73EB-7439; caller 46A8; *(2F05) range-select + rptb MAC + subc divide + *(2615) accum; HYPOTHESIS.
; ORIGIN 0x73EB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x596
	ld     *(0x2f05),a
	ld     a,b
	sub    #3,b
	stm    #12452,ar3
	xc     1,blt
	ld     #3,a
	sub    #22,b
	stm    #6,brc
	xc     1,bgt
	ld     #25,a
	stl    a,*(0x30ab)
	sub    #1,a
	sfta   a,1
	add    #12040,a
	stlm   a,ar2
	rptb   0x7408
	dld    *ar2+,a
	sfta   a,-12
	stl    a,*ar3+
	ld     #0,b
	ld     #8,16,a
	stm    #5,brc
	rptbd  0x7414
	stm    #12453,ar3
	maca   *ar3+,b
	add    #8,16,a
	ld     #0,a
	stm    #12452,ar3
	rpt    #6
	add    *ar3+,a
	stm    #12453,ar2
	sfta   b,-3
	sfta   a,-3
	stl    a,*ar2
	bc     0x7439,aeq
	sub    b,a
	bc     0x742b,agt
	rpt    #15
	subc   *ar2,b
	and    #-1,b
	add    #1,b
	sfta   b,-1
	xc     1,agt
	ld     #0,b
	ld     *(0x30ab),a
	sub    #3,a
	sfta   a,2
	add    a,b
	sub    #56,b
	stm    #9749,ar3
	add    *ar3,b
	stl    b,*ar3
	ret
