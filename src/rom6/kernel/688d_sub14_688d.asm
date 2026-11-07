; ROM6 0x688D SUB14_688D -- 21w, symbols.yaml data_word.
; Evidence: Bound 688D-68A0 (21w; exit retd FE00@689F + delay E800@68A0 byte-verified); post-688C-ret head (FC00@688C closes the SUB14_687F span).
; Wave-13: retd second delay @68A1 annexed (gap orphan; max b always runs).
; ORIGIN 0x688D
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x51e),#2048
	ld     *(0x2fd7),b
	xc     2,ntc
	ld     *(0x915),b
	neg    b
	add    #2,b
	nop
	nop
	xc     2,blt
	add    #51,b
	rc     tc
	sub    *ar6,b
	retd
	ld     #0,a
	max    b
