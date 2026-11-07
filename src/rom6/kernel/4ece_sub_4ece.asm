; ROM6 0x4ECE SUB_4ECE -- 18w, symbols.yaml data_word.
; Evidence: Bound 4ECE-4EDF (exit FE00@4EDD + slots 4EDE/4EDF); entry ld *(0x2f1d); callers F074 @4C25/4D90 (call 0x4ece); BC@4ED0 falls through; preceded by FC00@4ECD; HYPOTHESIS.
; ORIGIN 0x4ECE
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x2f1d),b
	bc     0x4ed5,bneq
	orm    #512,*(0x264e)
	bitf   *(0x2628),#16
	stl    b,*(0x9c7)
	ld     #0,b
	xc     1,tc
	ld     #1,b
	retd
	stl    b,*(0x9c6)
