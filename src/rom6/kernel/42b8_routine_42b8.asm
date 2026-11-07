; ROM6 0x42B8 ROUTINE_42B8 -- 91w, symbols.yaml data_word.
; Evidence: Bound 42B8-4312 (91w; exit RET FC00@4312 byte-verified; tail 4313-4314 2w dark); entries calld F274@7C4C->42B8 byte-verified + post-RET head (FC00@42B7); interior F847@42C7->42CB +
; ORIGIN 0x42B8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x606
	sth    a,*ar2+
	sth    b,*ar2+
	stm    #96,ar5
	abs    a
	abs    b
	dst    a,*ar5
	max    a
	exp    a
	nop
	ldm    t,a
	sub    #16,a
	bc     0x42cb,aleq
	stm    #16,t
	dld    *ar5,a
	norm   a
	norm   b
	and    #32767,16,a
	and    #32767,16,b
	sfta   a,-1
	sfta   b,-1
	sth    a,*ar5
	add    *ar5,16,b,a
	sub    *ar5,16,b
	st     #0,*(0xb)
	bc     0x4313,aeq
	sth    b,*ar5
	bit    *ar5,0
	abs    b
	sfta   b,-1
	sfta   a,-1
	sth    a,*ar5
	rpt    #14
	subc   *ar5,b
	and    #32767,b,a
	sfta   a,1
	xc     1,tc
	neg    a
	sfta   a,-2
	sfta   a,15
	sfta   a,1
	sth    a,*ar2
	mpya   *ar2+
	sfta   b,2
	sth    b,*ar2
	ld     *ar2,t
	stm    #3,brc
	rptb   0x42f7
	mpya   b
	sth    b,2,*ar2
	ld     *ar2+,16,a
	stm    #-20327,ar5
	mar    *+ar2(0xfffb)
	ld     #0,a
	rpt    #4
	mac    *ar2+,*ar5+,a
	mar    *+ar2(0xfff9)
	sfta   a,1
	add    #6434,16,a
	st     #0,*(0x8)
	bit    *ar2+,0
	ld     #25736,16,b
	sub    a,b
	xc     1,tc
	ld     b,a
	bit    *ar2,0
	nop
	nop
	xc     1,tc
	neg    a
	ret
