; ROM6 0x9BC3 FRAG_9BC3 -- 50w, symbols.yaml data_word.
; Evidence: Bound 9BC3-9BF4 (exit F073@9BF3->9C15 + operand 9BF4; TRIMMED: two more outside early-outs F073@9BF6/@9C11->9C15); entry F843@9BBA (byte-verified bc alt); interior F273 bd@9BE2->9B
; ORIGIN 0x9BC3
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0x2f00,ar2
	mvdm   0x2f01,ar4
	mvdm   0x2f02,ar6
	call   0x9c4d
	ldm    ar7,a
	bc     0x9bbe,aeq
	stm    #0,ar6
	mvmm   ar6,ar5
	stm    #12032,ar1
	xorm   #1,*(0x14)
	mvmm   ar6,ar3
	mvmm   ar6,ar7
	banz   0x9bdb,*ar4
	mar    *ar2+%
	mar    *ar6+
	banz   0x9be6,*ar4
	ld     *ar2,-8,b
	mar    *ar4+
	mar    *ar6+
	bd     0x9beb
	and    #255,b
	ld     *ar2+%,b
	mar    *ar4-
	mar    *ar6+
	and    #255,b
	sub    #193,b,a
	bc     0x9bf5,aeq
	sub    #125,b,a
	bc     0x9bf8,aeq
	b      0x9c15
