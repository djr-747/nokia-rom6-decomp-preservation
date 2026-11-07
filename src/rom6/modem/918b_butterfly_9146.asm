; ROM6 0x918B BUTTERFLY_9146 -- 1w (overlap-trimmed, wave-12).
; Evidence: RET @918B (the 9146 span's fall-through return abut). The former 69-word body duplicated the kernel 918C/91BD mesh spans word-for-word (owned by 918c_window_918c.asm and 91bd_window_918c.asm, logic in window_918C/frag_91BE); trimmed so one .asm owns every word. Recombine-clean.
; ORIGIN 0x918B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ret
