; ROM6 0x7C2F FRAG_7C2F -- 39w, symbols.yaml data_word.
; Evidence: Bound 7C2F-7C55 (39w; NO exit-class in-span — falls into SUB84_7C03 parsed bound [7C56-7CA9], no- exit tail abut per 6753/810A precedent; pre-word 7BEE not post-RET — entry is bran
; ORIGIN 0x7C2F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5a0
	stm    #12452,ar2
	stm    #1,ar0
	dst    a,*ar2+
	dst    a,*ar2-
	stm    #12196,ar4
	stm    #31,brc
	rptb   0x7c49
	dld    *ar4+,a
	banz   0x7c42,*ar0
	neg    a
	nop
	dld    *ar4+,b
	xc     1,ageq
	neg    b
	abs    a
	dadd   *ar2+,a
	dadd   *ar2-,b
	dst    a,*ar2+
	dst    b,*ar2-
	banz   0x7c39,*ar0-
	calld  0x42b8
	stm    #12452,ar2
	sfta   a,-16
	cmpm   *(0x13),#1
	rc     tc
	sfta   a,-1
