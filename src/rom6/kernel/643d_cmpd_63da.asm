; ROM6 0x643D CMPD_63DA -- 1w (overlap-split wave-12).
; Evidence: RET FC00 @0x643D (the 63DA span's fall-through return abut). The former 96-word body duplicated the 643E span (owned by 643e_sub13_643e.asm, logic in sub13_643E) and the 644A span head (owned by 644a_sub13_643e.asm, logic in sub13_644A); the unique tail lives in the new 6458 span. Split so one .asm owns every word. Recombine-clean.
; ORIGIN 0x643D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
