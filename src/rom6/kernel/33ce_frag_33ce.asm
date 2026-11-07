; ROM6 0x33CE FRAG_33CE -- 10w, symbols.yaml data_word.
; Evidence: Bound 33CE-33D7 (10w, exit RET FC00@33D7); post-ret entry (FC00@33CD of FRAG_33BC); entry words 7714/2512; zero refs/calls; clean leaf; HYPOTHESIS.
; ORIGIN 0x33CE
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #9490,ar4
	ld     *(0x11),b
	andm   #-33,*ar4
	xc     2,bneq
	orm    #32,*ar4
	ret
