; ROM6 0x3FFA ROUTINE_3FFA -- 13w, symbols.yaml data_word.
; Evidence: Bound 3FFA-4006 (13w; exit RET FC00@4006 byte-verified; tail 4000-4006 (4EF8 01FE / F495 75F8 / 0008 0019) falls through from 3FFA head — single execution unit; head F074 064A call
; ORIGIN 0x3FFA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x64a
	nop
	portw  *(0x9),24
	dst    a,*(0x1fe)
	nop
	portw  *(0x8),25
	ret
