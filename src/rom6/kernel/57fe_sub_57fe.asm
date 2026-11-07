; ROM6 0x57FE SUB_57FE -- 13w, symbols.yaml data_word.
; Evidence: Entry F074 059C 7712 0912; bound 57FE-580A; callers F074@51F8(ext)/5738(int); body call 059C + calld 425F@5806; HYPOTHESIS.
; ORIGIN 0x57FE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #2322,ar2
	stm    #2332,ar3
	rpt    #8
	mvdd   *ar2+,*ar3+
	calld  0x425f
	stm    #2332,ar2
	ret
