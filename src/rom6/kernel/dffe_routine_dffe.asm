; ROM6 0xDFFE ROUTINE_DFFE -- 2w, symbols.yaml data_word.
; Evidence: Bound DFFE-DFFF (2w micro: st #1,DP+0x63 2w, NO own exit — runs into FIR_KERNEL_A head; tail-frag abut, not a routine); entry call F074@DFF6->DFFE byte-verified (exterior from PORT
; ORIGIN 0xDFFE
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #1,0x63
