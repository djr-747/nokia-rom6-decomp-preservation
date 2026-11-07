; ROM6 0x9A82 FRAG_9A82 -- 61w, symbols.yaml data_word.
; Evidence: Bound 9A82-9ABE (exit F073@9ABD->9AD2 objdump); entries 6x bc (F844/F842/F830 @9A58/62/67/6D/76/7C); interior call 0710, joins 9AA8/9AB7/9ABA/9ABF (rptb@9A3B->9A41 belongs to FRAG_
; ORIGIN 0x9A82
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x710
	andm   #-33,*(0x20ff)
	ld     #120,a
	ssbx   st1,intm
	ld     *ar3,b
	min    a
	sub    a,b
	pshm   ar2
	pshm   al
	bitf   *(0x20ff),#-32768
	stl    b,*ar3
	ld     a,b
	ld     #0,a
	xc     1,tc
	ld     #1,a
	nop
	nop
	pshm   al
	rsbx   st1,intm
	stm    #12032,ar3
	stlm   b,ar5
	bitf   *(0x20ff),#-32768
	bc     0x9abf,ntc
	sfta   b,-1
	bc     0x9aa8,nc
	andm   #32767,*(0x20ff)
	bitf   *(0x20ff),#-32768
	ld     *ar2+%,16,a
	sub    #1,b
	stlm   b,brc
	bc     0x9aba,blt
	rptb   0x9ab7
	or     *ar2+%,a
	stl    a,-8,*ar3+
	sftl   a,8
	sftl   a,8
	xc     1,tc
	mar    *ar2-%
	xc     2,ntc
	stl    a,-8,*ar3
	b      0x9ad2
