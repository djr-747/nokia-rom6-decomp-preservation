; ROM6 0x5AAC ROUTINE_5AAC -- 28w, symbols.yaml data_word.
; Evidence: Bound 5AAC-5AC7 (28w; branch-tailed exit B F073@5AC6->5ACA + operand 5AC7 — first-outside 5AC6, end 5AC7, no RET in span, exits forward into SEG_5AC8+2; exit scan otherwise clean);
; ORIGIN 0x5AAC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	mvmm   ar2,ar4
	stm    #9804,ar1
	ld     #8,b
	ld     *ar1,a
	sub    b,a
	stm    #456,bk
	stm    #0,ar0
	xc     2,alt
	add    #22,a
	mpy    *(0x8),#114,a
	cmpm   *(0x250f),#34
	bc     0x5ac8,ntc
	add    *(0x352c),2,a
	b      0x5aca
