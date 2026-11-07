; ROM6 0x8936 FRAG_8936 -- 32w, symbols.yaml data_word.
; Evidence: Bound 8936-8955 (exit F073@8954->891C rejoin); entry F830@8918 (objdump bc tc->8936); interior call 89F4@8946, banzd loop 8950->8946; HYPOTHESIS.
; ORIGIN 0x8936
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1370,ar2
	ld     *ar2,a
	sub    #5,a,b
	bc     0x89b3,bgeq
	add    #1,a
	stl    a,*ar2
	stm    #12090,ar2
	stm    #3,ar5
	stm    #4348,ar1
	call   0x89f4
	and    #3,16,a
	sth    a,*ar2(0xfffc)
	ld     *ar2,b
	sub    #11,b
	ld     #0,a
	banzd  0x8946,*ar5-
	max    b
	stl    b,*ar2+
	b      0x891c
