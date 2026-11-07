; ROM6 0x36B0 FRAG_36B0 -- 18w, symbols.yaml data_word.
; Evidence: Bound 36B0-36C1 (18w; exit B F073@36C0->2E64 + operand 36C1 — dispatch-loop trampoline; exit scan clean; pre-word 36C2 not post-RET); entry bc F830@998->36B0 byte-verified (block01
; ORIGIN 0x36B0
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #10217,ar3
	st     #11,*ar3+
	st     #1,*ar3+
	stm    #158,ar4
	stm    #10217,ar3
	stm    #4,ar5
	call   0x2c88
	call   0x2e2f
	b      0x2e64
