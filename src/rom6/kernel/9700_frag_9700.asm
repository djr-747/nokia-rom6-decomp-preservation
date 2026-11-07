; ROM6 0x9700 FRAG_9700 -- 8w, symbols.yaml data_word.
; Evidence: Bound 9700-9707 (8w; exit B F073@9706->970B + operand 9707 — branch-tailed into dark 970B-lane; exit scan otherwise clean; pre-word F4EB trete, not post-RET — entry is branch-based
; ORIGIN 0x9700
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar4,#64
	bc     0x9708,ntc
	call   0x978f
	b      0x970b
