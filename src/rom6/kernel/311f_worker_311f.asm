; ROM6 0x311F WORKER_311F -- 64w, symbols.yaml data_word.
; Evidence: Entry 6F82 0C56 (ld *ar2,-10,a...), post-ret (FC00@311E); bound 311F-315E (64w, exit F073@315D->2E64); no callers; no interior calls/joins; clean leaf; HYPOTHESIS.
; ORIGIN 0x311F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,-10,a
	and    #15,a
	add    #2,a
	stl    a,*(0x587)
	ld     *ar2+%,a
	and    #255,a,b
	and    #768,a
	sfta   a,-8
	bcd    0x313e,aeq
	or     #2048,b
	sub    #2,a
	nop
	nop
	xc     2,alt
	or     #1024,b
	xc     2,aeq
	or     #256,b
	xc     2,agt
	or     #512,b
	stl    b,*(0x2202)
	ld     *ar2+%,a
	and    #-256,a,b
	sfta   b,-8
	mpy    *(0xb),#347,b
	sfta   b,-4
	stl    b,*(0x2204)
	and    #255,a
	sub    #255,a,b
	mpy    *(0x8),#3467,a
	sfta   a,-4
	xc     2,beq
	ld     #-1,a
	stl    a,*(0x2203)
	call   0x2e2f
	pshm   ar2
	call   0x98ad
	popm   ar2
	b      0x2e64
