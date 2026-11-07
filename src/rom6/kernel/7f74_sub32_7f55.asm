; ROM6 0x7F74 SUB32_7F55 -- 1w (overlap-split wave-12).
; Evidence: RET FC00 @0x7F74 (prior span fall-through return abut). Former body duplicated the 7F75 span word-for-word (owned by 7f75_sub_7f75.asm). Split so one .asm owns every word. Recombine-clean.
; ORIGIN 0x7F74
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret