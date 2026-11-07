; ROM6 0x90B8 KERNEL_9071 -- 1w -- overlap-split wave-12.
; Evidence: RET FC00 @0x90B8 (9070-function fall-through abut; 9070 span ends 90B7, F1 starts 90B9). Former giant body (F1/F2/F3/F4-head dups) re-homed to 90b9/90d6/90e7/90f8 owners. Recombine-clean.
; ORIGIN 0x90B8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
