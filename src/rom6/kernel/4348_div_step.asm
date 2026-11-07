; ROM6 0x4348 DIV_STEP_4348 -- 7w, call+rpt/subc+retd+delay spill.
; Absolute call target 0x0606 assembles as-is (boot-page helper).
; ORIGIN 0x4348
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x606
	rpt #14
	subc *ar4,a
	retd
	and #32767,a
