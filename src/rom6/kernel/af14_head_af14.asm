; ROM6 0xAF14 HEAD_AF14 -- 2w (dark-gap wave-13).
; Evidence: Post-ret call head (follows aeec ret @AF13); call 0x59A (dark, sub_059A forward extern). No known callers; entry unconfirmed, flagged. C intent in af14_head_af14.c. Recombine-clean.
; ORIGIN 0xAF14
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59a
