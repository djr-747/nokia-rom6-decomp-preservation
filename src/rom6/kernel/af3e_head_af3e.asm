; ROM6 0xAF3E HEAD_AF3E -- 2w (dark-gap wave-13).
; Evidence: Post-ret call head (follows af16 ret @AF3D); call 0x59A (dark, sub_059A forward extern). No known callers; entry unconfirmed, flagged. C intent in af3e_head_af3e.c. Recombine-clean.
; ORIGIN 0xAF3E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59a
