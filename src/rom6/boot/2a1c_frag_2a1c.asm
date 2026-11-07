; ROM6 0x2A1C FRAG_2A1C -- 32w, symbols.yaml data_word.
; Evidence: Bound 2A1C-2A3B (32w; exit B F073@2A3A->2A8A + operand 2A3B, byte-verified; exit scan clean); entry bc F820@2A10->2A1C byte-verified (chained from FRAG_2A0E interior); vestibule ar
; ORIGIN 0x2A1C
	.sect ".text"
	.mmregs
	.global _start
_start:
	cmpm   *(0x250f),#34
	bc     0x2a3c,ntc
	bitf   *ar3,#32
	bc     0x2a3c,ntc
	call   0x3ee1
	add    *(0x3ee7),a
	sub    *(0x36a),a,b
	st     #64,*ar3
	stm    #4724,ar3
	stm    #4718,ar2
	xc     1,bgt
	ld     b,a
	dld    *(0x3ef6),b
	dst    b,*ar3
	st     #256,*ar2+
	stl    a,*ar2-
	b      0x2a8a
