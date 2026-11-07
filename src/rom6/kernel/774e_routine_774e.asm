; ROM6 0x774E ROUTINE_774E -- 66w, symbols.yaml data_word.
; Evidence: Bound 774E-778F (66w; exit RET FC00@778F byte-verified, exit scan clean); entry call F074@74A2-> 774E byte-verified + post-RET head (FC00@774D = FRAG_772F exit); abuts FRAG_772F (e
; ORIGIN 0x774E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #12172,ar3
	stm    #12480,ar2
	dld    *ar3+,a
	dadd   *ar3+,a
	dadd   *ar3+,a
	dadd   *ar3,a
	dst    a,*ar2+
	dsub   *ar3,a
	dsub   *ar3-,a
	dst    a,*ar2
	dsub   *ar3,a
	dsub   *ar3+,a
	dst    a,*+ar2(0x4)
	dadd   *ar3,a
	dadd   *ar3,a
	dst    a,*+ar2(0xfffe)
	dsub   *+ar3(0xfffc),a
	dsub   *ar3+,a
	dst    a,*+ar2(0x8)
	dadd   *ar3,a
	dadd   *ar3+,a
	dst    a,*+ar2(0xfffc)
	dsub   *ar3,a
	dsub   *ar3-,a
	dst    a,*+ar2(0x2)
	dsub   *ar3,a
	dsub   *ar3,a
	dst    a,*+ar2(0x4)
	stm    #12480,ar2
	stm    #7,brc
	rptbd  0x778e
	stm    #12035,ar4
	ld     *(0x2f04),t
	dld    *ar2,a
	norm   a
	sfta   a,12
	mpya   *ar4
	stm    #0,al
	abs    a
	bc     0x778d,aeq
	call   0x4348
	xc     1,blt
	neg    a
	sfta   a,-2
	stl    a,*ar2+
	mar    *ar2+
	ret
