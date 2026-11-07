; ROM6 0x3EE3 STABLE_READ_3EE3 -- 16w, program_word (new, wave-19bx).
; Evidence: Linear fall-through from the 3EE1 stub head (F074 063E@3EE1, existing 2w module); bound 3EE3-3EF2 (exit RET FC00@3EF2 byte-verified); port-13 double-read stability loop; no other entries.
; ORIGIN 0x3EE3
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,a
	portr  13,*(0x8)
	and    #16383,a
	ld     a,b
	portr  13,*(0x8)
	and    #16383,a
	sub    a,b
	bc     0x3ee9,bneq
	ret
