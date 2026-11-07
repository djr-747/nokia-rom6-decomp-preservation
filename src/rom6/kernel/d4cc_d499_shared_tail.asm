; ROM6 0xD4CC D499_SHARED_TAIL -- 2w, symbols.yaml data_word.
; Evidence: Entered only via 0xD45A bc bneq (intra-span); interior calld 0xD39E @D49D + call 0xDB81 @D4C4; cond rc @D4CA; first exit retd FE00 @D4CB +2 delays (Bound D4CC-D4CD, executed delay 
; ORIGIN 0xD4CC
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdk   *ar6,0xb60
