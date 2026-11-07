; ROM6 0x4384 DIV_CORE_4384 -- 54w, symbols.yaml data_word.
; Evidence: Entry F074 0606; RPTB + TDSUB divide-loop form; first-RET FC00 @0x43B9; 10 calld callers 5717...7274; no port ops; HYPOTHESIS divide core.
; Pool: divide core -- TSUB trial-subtract, TLD double-load, and DST-indirect double-store have no ti-c54x oracle leaf or catalog row (only DST_SMEM_ABSOLUTE exists); the rptb/bd-driven TSUB loop plus exp/norm scaling therefore has no grounded C form. stays .asm, bytes verified.
; ORIGIN 0x4384
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x606
	pshd   *ar4
	pshm   ar7
	sub    *ar4,a,b
	bc     0x43b6,blt
	exp    a
	ld     *ar4,b
	st     t,*ar2
	exp    b
	stm    #96,ar7
	ldm    t,b
	sub    *ar2,b
	stl    b,*ar2
	stlm   b,brc
	stlm   b,t
	ld     *ar4,b
	norm   b
	dst    b,*ar7
	st     #1,*ar4
	ld     a,b
	rptb   0x43a7
	dsub   *ar7,a
	bc     0x43a6,alt
	bd     0x43a7
	sfta   a,1
	or     *ar4,a
	sfta   b,1,a
	ld     a,b
	dst    a,*ar7
	ldm    t,a
	stlm   a,brc
	ld     #0,a
	rptb   0x43af
	sftl   a,1
	or     *ar4,a
	and    a,b
	dld    *ar7,a
	rpt    *ar2
	sftl   a,-1
	b      0x43b7
	ld     #0,b
	popm   ar7
	popd   *ar4
	ret
