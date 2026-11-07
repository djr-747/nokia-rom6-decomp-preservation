; ROM6 0x361C FRAG_361C -- 7w, symbols.yaml data_word.
; Evidence: Bound 361C-3622 (7w; exit B F073@3621->2E64 + operand 3622 — dispatch trampoline tail, like 3674 family; exit scan clean); post-RET head only (FC00@361B = FRAG_3616 exit, zero exte
; ORIGIN 0x361C
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x54d),#4
	bc     0x3623,ntc
	b      0x2e64
