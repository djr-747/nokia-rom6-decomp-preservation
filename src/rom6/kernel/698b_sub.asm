; ROM6 0x698B SUB_6993 -- 30w, calls+bc+calld+xc+retd+spill.
; Absolute targets (0x0598, 0x4384, 0x69A6) assemble as-is.
; ORIGIN 0x698B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x598
	ld *(0x91f),a
	sub #50,a,b
	bc 0x69a6,beq
	call 0x598
	ldu *ar1,a
	stm #9484,ar4
	calld 0x4384
	stm #12049,ar2
	and #-1,a
	neg a
	add *(0x2513),a
	ld a,b
	add *(0x250c),a
	xc 1,bgeq
	ld b,a
	retd
	stl a,*(0x563)
