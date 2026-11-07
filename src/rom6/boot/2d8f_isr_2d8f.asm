; ROM6 0x2D8F ISR_2D8F -- 85w, symbols.yaml data_word.
; Evidence: Entry F074 0624 11F8 0853 6FF8 0852 0E20 FC45; bound 2D8F-2DE3; caller F074@2E94; HPI *(0x853)/(0x852) + stl *(0x54C) + staged 2F00 + calls 0624/93CE@2DD9; HYPOTHESIS.
; ORIGIN 0x2D8F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x624
	ld     *(0x853),b
	sub    *(0x852),b,a
	rc     aeq
	add    #2048,b
	stlm   b,ar2
	ld     #768,a
	adds   *ar2,a
	add    a,-9,b
	sub    #2129,b,a
	bc     0x2da4,aleq
	sub    #82,b
	sub    #2048,b
	stm    #82,bk
	stl    b,*(0x54c)
	ldu    *ar2+%,b
	bitf   *(0x54d),#8
	and    #255,b,a
	sftl   b,-8
	rc     ntc
	pshm   bk
	pshm   al
	pshm   ah
	pshm   ag
	pshm   bl
	pshm   bh
	pshm   bg
	pshm   ar2
	and    #255,a
	or     b,8,a
	stlm   a,ar0
	stm    #12032,ar3
	ldm    ar0,a
	st     #1024,*ar3+
	stl    a,*ar3+
	bc     0x2dd2,beq
	add    #1,b,a
	sftl   a,-1
	sub    #1,a
	stlm   a,brc
	nop
	nop
	rptb   0x2dd1
	ld     *ar2+%,a
	stl    a,*ar3+
	add    #4,b
	stm    #12032,ar2
	ld     #20,a
	stm    #244,ar0
	call   0x93ce
	popm   ar2
	popm   bg
	popm   bh
	popm   bl
	popm   ag
	popm   ah
	popm   al
	popm   bk
	ret
