; ROM6 0x2262 SUB_2262 -- 10w, symbols.yaml program_word.
; Evidence: Exterior calld x5 (0x4516/0x451E/0x4524/0x54D7 + in-gap); call-2282 + rc + mvmd + calld-2D5E + ret; no other entries, evidenced, flagged.
; ORIGIN 0x2262
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x2282
	rc tc
	mvmd ar2,0x536
	calld 0x2d5e
	stm #2161,ar3
	ret
