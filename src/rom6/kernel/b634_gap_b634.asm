; ROM6 0xB634 GAP_B634 -- 178w, symbols.yaml data_word.
; Evidence: Post-RET entry 4A15 4A14 4A11 10F8 04FA F010; caller F074@2784 (objdump call 0xb634); first-RET @0xB6E5 (178w, ends at existing 0xB6E6); HYPOTHESIS. Wave-7: block00 loader branch-t
; ORIGIN 0xB634
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   ar5
	pshm   ar4
	pshm   ar1
	ld     *(0x4c8),a
	sub    #1,a
	stl    a,*(0x4c8)
	bc     0xb668,agt
	ld     *(0x4c5),a
	sub    #2,a,b
	bc     0xb64d,bneq
	st     #0,*(0x4c7)
	st     #100,*(0x4c8)
	b      0xb668
	sub    #3,a,b
	bc     0xb662,bneq
	mvdk   *(0x856),0x4d1
	ld     #1,b
	call   0xb4a8
	st     #0,*(0x4c6)
	st     #0,*(0x4c7)
	st     #1,*(0x4c8)
	b      0xb668
	add    #1,a
	stl    a,*(0x4c5)
	call   0x6b4
	ld     *(0x4c6),a
	add    *(0x4c7),a
	and    #-32768,a,b
	bc     0xb672,beq
	ld     #32767,a
	bc     0xb675,ageq
	ld     #0,a
	stl    a,*(0x4c6)
	ld     *(0x4c6),t
	mpyr   *(0x85b),b
	sfta   b,-15
	stlm   b,t
	stm    #1229,ar3
	stm    #1225,ar4
	stm    #1219,ar5
	stm    #-17492,ar1
	ld     *ar4,b
	add    *ar3+,b
	and    #-1,a
	stl    b,*ar4+
	ld     b,-8,a
	and    *ar1+,a
	sftl   b,-15
	sub    *ar1-,a
	abs    a
	add    *ar5,a
	stlm   a,ar2
	nop
	nop
	ld     *ar2,a
	xc     1,bneq
	neg    a
	nop
	pshm   al
	pshm   ah
	pshm   ag
	ld     *ar4,b
	add    *ar3+,b
	stl    b,*ar4+
	ld     b,-8,a
	and    *ar1+,a
	sftl   b,-15
	sub    *ar1-,a
	abs    a
	add    *ar5,a
	stlm   a,ar2
	nop
	nop
	ld     *ar2,a
	xc     1,bneq
	neg    a
	sfta   a,-1
	popm   bg
	popm   bh
	popm   bl
	add    b,a
	nop
	pshm   al
	pshm   ah
	pshm   ag
	ld     *ar4,b
	add    *ar3+,b
	stl    b,*ar4+
	ld     b,-8,a
	and    *ar1+,a
	sftl   b,-15
	sub    *ar1-,a
	abs    a
	add    *ar5,a
	stlm   a,ar2
	nop
	nop
	ld     *ar2,a
	xc     1,bneq
	neg    a
	sfta   a,-1
	popm   bg
	popm   bh
	popm   bl
	add    b,a
	nop
	pshm   al
	pshm   ah
	pshm   ag
	ld     *ar4,b
	add    *ar3+,b
	stl    b,*ar4+
	ld     b,-8,a
	and    *ar1+,a
	sftl   b,-15
	sub    *ar1-,a
	abs    a
	add    *ar5,a
	stlm   a,ar2
	nop
	nop
	ld     *ar2,a
	xc     1,bneq
	neg    a
	sfta   a,-1
	popm   bg
	popm   bh
	popm   bl
	add    b,a
	sfta   a,8
	sfta   a,7
	mpya   a
	sfta   a,1
	popm   ar1
	popm   ar4
	popm   ar5
	ret
