; ROM6 0xDD99 ABS_ACCUM_DD77 -- 2w, symbols.yaml data_word.
; Evidence: Entry 7712 0062 7713 FBA6 (FBA6 = stm -1114 immediate, not branch -- operand trap avoided); caller F074 @D183 verified; first exit retd FE00 @DD98 +delays (Bound DD99-DD9A, execute
; ORIGIN 0xDD99
	.sect ".text"
	.mmregs
	.global _start
_start:
	add    *ar2,-2,a
