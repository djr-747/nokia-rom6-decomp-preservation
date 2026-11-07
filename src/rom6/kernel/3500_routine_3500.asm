; ROM6 0x3500 ROUTINE_3500 -- 29w, symbols.yaml data_word.
; Evidence: Entry 6FF8/04FA/0C43 (ld *(0x4FA),3,a); interior target 0x350C (3x F074 callers 34EC/34EE/34F0); fall-through first-RET FC00 @0x351C; HYPOTHESIS shared-tail.
; ORIGIN 0x3500
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x4fa),3,a
	or     *(0x866),a
	or     #64,a
	stl    a,*(0x866)
	idle   3
	b      0x3500
	ld     *ar2,a
	and    #-3856,a
	ld     *ar2+%,8,b
	and    #3840,b
	or     b,a
	ld     *ar2,-8,b
	and    #15,b
	or     b,a
	xor    *ar5+,a
	bc     0x3500,aneq
	ret
