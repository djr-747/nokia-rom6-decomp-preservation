; ROM6 0x2FD3 SUB_2FD3A -- 21w, symbols.yaml program_word.
; Evidence: Bound 2FD3-2FE7 (21w); entry TRACE (3310 chain run docs/evidence/dsp-pchist-3310-chain-20261106/pchist.txt: 2FD3 heads x1); continuation of SUB_2F51 past its 2FD1 dispatch tail; ld
; ORIGIN 0x2FD3
	.sect ".text"
	.global _start
_start:
	ldu    *ar2+%,a
	and    #255,a,b
	sftl   a,-8
	stlm   b,ar3
	and    #2,a,b
	bc     0x2fe8,beq
	orm    #512,*(0x2549)
	and    #1,a,b
	bc     0x2ff2,bneq
	orm    #512,*(0x2512)
	b      0x2ff2
