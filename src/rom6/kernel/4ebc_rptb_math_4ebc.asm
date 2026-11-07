; ROM6 0x4EBC RPTB_MATH_4EBC -- 18w, symbols.yaml data_word.
; Evidence: Entry 771A 0038 F072 4ECC; bound 4EBC-4ECD; callers 4x calld 4E9E/4EA3/4EAA/4EAF; brc-56 rptb mvdk/sfta/mpya/sth leaf; HYPOTHESIS.
; ORIGIN 0x4EBC
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #56,brc
	rptb   0x4ecc
	mvdk   *ar2+,0x13
	mar    *ar3+0
	ld     *ar3,16,b
	sfta   b,12
	sfta   b,8
	sfta   b,-8
	sfta   b,-11
	ld     #1,16,a
	add    b,a
	mpya   *ar4
	sth    b,asm,*ar3
	ret
