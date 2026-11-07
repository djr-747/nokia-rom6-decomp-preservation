; ROM6 0xB61F FRAG_B61F -- 21w, symbols.yaml data_word.
; Evidence: Bound B61F-B633 (21w; exit RET FC00@B633 byte-verified, exit scan clean); entries bc F84C@B614-> B61F byte-verified (exterior) + post-RET head (FC00@B61E = FRAG_B605 exit); HYPOTHE
; ORIGIN 0xB61F
	.sect ".text"
	.mmregs
	.global _start
_start:
	sfta   b,3
	stl    b,*ar2
	sfta   a,8
	sfta   a,8
	mpya   *ar2
	abs    a
	sfta   a,-16
	rpt    #15
	subc   *ar2,a
	stl    a,*ar2
	ld     #0,a
	sub    *ar2,a
	xc     1,blt
	stl    a,*ar2
	mar    *ar2+
	ld     *ar3,a
	and    #255,a
	sfta   a,3
	stl    a,*ar2
	ret
