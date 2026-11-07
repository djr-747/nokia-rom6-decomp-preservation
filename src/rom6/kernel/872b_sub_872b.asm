; ROM6 0x872B SUB_872B -- 74w, symbols.yaml data_word.
; Evidence: Bound 872B-8774 (exit FE00@8772 + slots 8773/8774); callers F274 @878B (internal forward) + @A740/@A948 (calld 0x872b x3); interior label 8775 (rptb block, 3x internal CD 8761/8766
; ORIGIN 0x872B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x592
	rsbx   st1,sxm
	rsbx   st0,tc
	mvmm   ar4,ar5
	mar    *+ar5(0xa)
	ld     *ar5,a
	stm    #8,brc
	rptbd  0x873b
	stm    #12032,ar2
	ror    a
	rol    b
	roltc  b
	sftl   b,14
	ld     *ar4(0x1),16,a
	stm    #8,brc
	rptbd  0x8747
	dst    b,*ar2
	sftl   a,7
	roltc  b
	rol    a
	rol    b
	sftl   b,14
	dadd   *ar2,b,a
	sftl   a,-14,b
	ld     *ar4,16,a
	stm    #15,brc
	rptbd  0x8754
	pshm   bh
	pshm   bl
	roltc  b
	rol    a
	rol    b
	ld     *ar5+,-9,a
	stm    #15,brc
	rptbd  0x875f
	dst    b,*ar2
	add    *ar5,7,a
	ror    a
	rol    b
	roltc  b
	dadd   *ar2,b,a
	calld  0x8775
	stm    #15,brc
	popm   ah
	calld  0x8775
	stm    #15,brc
	popm   ah
	calld  0x8775
	stm    #17,brc
	ld     #7,b
	and    b,a
	xor    b,a
	retd
	sftl   a,11
	ssbx   st1,sxm
