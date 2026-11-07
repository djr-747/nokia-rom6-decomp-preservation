; ROM6 0x7C56 SUB84_7C03 -- 1w (overlap-trimmed wave-12).
; Evidence: RET FC00 @0x7C56 (prior span's fall-through return abut). The former 84-word body duplicated the 7C57 span word-for-word (owned by rf/7c57_check_dispatch_7c57.asm, logic in sub_7C57), the 7C9E span head (owned by 7c9e_counter_step_7c9e.asm, logic in its C), and the 7CA5 span head (owned by 7ca5_sub_7ca5.asm). Trimmed so one .asm owns every word. Recombine-clean.
; ORIGIN 0x7C56
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
