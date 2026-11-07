; ROM6 0x5BD9 SUB_5BD9 -- 24w, symbols.yaml data_word.
; Evidence: Bound 5BD9-5BF0 (exit FC00@5BF0 = gap end); callers 4x F274 @5B4D/5B56 (ext) + @5B6D/5B76 (int, calld 0x5bd9); rptb loop; touches existing SUB_5BF1, no overlap; HYPOTHESIS.
; ORIGIN 0x5BD9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x674
	stm    #56,brc
	rptb   0x5bef
	ld     a,-2,b
	stlm   b,ar3
	and    #3,a,b
	ld     b,2,b
	stlm   b,t
	ld     0x0b,asm
	ld     #15,b
	mar    *ar3+0
	ld     b,asm
	cmpl   b
	and    *ar3,b
	add    *ar4,ts,b
	stl    b,*ar3
	dld    *ar4+,a
	ld     *ar5+,a
	add    0x17,a
	ret
