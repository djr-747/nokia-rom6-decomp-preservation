; ROM6 0x836C SUB56_8335 -- 1w (overlap-split wave-12).
; Evidence: ret FC00 @0x836C (8335-function exit; 8334 span ends 836B). Former body duplicated 836D-838B + 838C-839F + 83A0-83A3 (owned by 836d extended 31w, 838c, 83a0). Recombine-clean.
; ORIGIN 0x836C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
