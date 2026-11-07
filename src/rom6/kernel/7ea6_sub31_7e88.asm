; ROM6 0x7EA6 SUB31_7E88 -- 1w (overlap-split wave-12).
; Evidence: RET FC00 @0x7EA6 (the 7E88 span's fall-through return abut). The former body duplicated the 7EA7 span (owned by 7ea7_bit_merge_7ea7.asm, logic in its span) and the 7EB1 lanes (owned by the new 7eb1 span). Split so one .asm owns every word. Recombine-clean.
; ORIGIN 0x7EA6
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
