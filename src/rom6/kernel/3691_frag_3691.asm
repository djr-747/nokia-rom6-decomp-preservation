; ROM6 0x3691 FRAG_3691 -- 16w, symbols.yaml data_word.
; Evidence: Bound 3691-36A0 (16w; exit B F073@369F->2E64 + operand 36A0 — dispatch-loop trampoline tail, like FRAG_3674/2E52/3616 family; exit scan clean; pre-word 05B2 not post-RET); entries 
; ORIGIN 0x3691
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2,a
	cmpm   *(0x8),#9
	bc     0x36a1,ntc
	ld     *(0x250f),b
	call   0x580b
	cc     0x84cf,tc
	call   0x2e2f
	b      0x2e64
