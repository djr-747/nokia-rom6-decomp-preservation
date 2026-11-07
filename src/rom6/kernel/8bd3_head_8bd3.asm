; ROM6 0x8BD3 HEAD_8BD3 -- 2w (dark-gap wave-13).
; Evidence: Post-retd call head (follows 8b9d retd delays @8BD1-8BD2); call 0x5B2 (sub_05B2 forward extern, 36fb precedent). No known callers; entry unconfirmed, flagged. C intent in 8bd3_head_8bd3.c. Recombine-clean.
; ORIGIN 0x8BD3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b2
