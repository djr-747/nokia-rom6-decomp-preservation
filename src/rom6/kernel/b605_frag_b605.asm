; ROM6 0xB605 FRAG_B605 -- 26w, symbols.yaml data_word.
; Evidence: Bound B605-B61E (26w; exit RET FC00@B61E byte-verified, exit scan clean); post-RET head (FC00@B604); no ext refs; no interior calls; tail B61F-B633 (21w) stays dark; HYPOTHESIS.
; ORIGIN 0xB605
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x4c4),a
	add    *(0x4c5),a
	stlm   a,ar3
	stm    #1222,ar2
	ld     *ar3,-1,a
	and    #32640,a
	sub    *ar2+,a
	ld     *ar3,b
	and    #255,b
	bc     0xb61f,bneq
	stl    b,*ar2-
	stl    b,*(0x4c8)
	ld     *ar3,-1,a
	and    #32640,a
	stl    a,*ar2
	ret
