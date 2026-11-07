; ROM6 0xAE70 RET_AE70 -- 1w (dark-gap wave-13).
; Evidence: RET FC00 @0xAE70 (jump-table closing boundary per ae6c intent; table AE6C-AE6F ends before it, ae71 routine starts after). Orphan ret-abut, entry unconfirmed; asm-only 1w (7f74/80fb precedent; no intent to model). Recombine-clean.
; ORIGIN 0xAE70
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
