; ROM6 0x56FC SUB_56FC -- 63w, symbols.yaml data_word.
; Evidence: Entry F074 059C 7711 247A; bound 56FC-573A (FC00@573A, 63w); callers F074@5550/6841; body call 059C + 5x calld 4384 + call 57FE (dedup: same head in small-gaps-west, emitted once);
; ORIGIN 0x56FC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #9338,ar1
	dld    *ar1,a
	rc     aeq
	stm    #2322,ar3
	dld    *ar3,b
	add    b,a
	st     #0,*ar1+
	st     #0,*ar1
	ld     #41,16,b
	or     #28672,b
	sub    b,a
	stm    #12032,ar2
	xc     1,alt
	add    b,a
	sth    a,*ar3+
	stl    a,*ar3-
	stm    #21,ar4
	calld  0x4384
	st     #26,*ar4
	stm    #2324,ar1
	stl    a,*ar1+
	dld    *ar3,a
	calld  0x4384
	st     #51,*ar4
	stl    a,*ar1+
	stl    b,*ar1+
	dld    *ar3,a
	calld  0x4384
	st     #102,*ar4
	stl    a,*ar1+
	dld    *ar3,a
	calld  0x4384
	st     #104,*ar4
	stl    a,*ar1+
	dld    *ar3,a
	calld  0x4384
	st     #1326,*ar4
	stl    a,*ar1+
	stl    b,*ar1
	call   0x57fe
	ret
