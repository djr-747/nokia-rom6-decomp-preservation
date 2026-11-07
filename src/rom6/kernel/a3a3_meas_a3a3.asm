; ROM6 0xA3A3 MEAS_A3A3 -- 27w (dark-gap wave-13).
; Evidence: Entry call F074@A26B/@A2AE (exterior, byte-verified); bound A3A3-A3BD (call 654; and; stm; ld; and; bc A3BE,beq; calld 0x40BC (delay orm runs first); ld; rc bneq; andm; call 3E53; ld; ret @A3BD). C intent in a3a3_meas_a3a3.c. Recombine-clean.
; ORIGIN 0xA3A3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x654
	and    #16384,b
	stm    #9785,ar2
	ld     *ar2,a
	and    #3072,a
	bc     0xa3be,beq
	and    #2048,a
	calld  0x40bc
	orm    #2048,*ar2
	ld     *(0x2634),b
	rc     bneq
	andm   #-3073,*(0x2639)
	call   0x3e53
	ld     #1,b
	ret
