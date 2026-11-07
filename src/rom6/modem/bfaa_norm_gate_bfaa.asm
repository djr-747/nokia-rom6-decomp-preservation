; ROM6 0xBFAA NORM_GATE_BFAA -- 13w, symbols.yaml data_word.
; Evidence: Entry F074 06DE; bound BFAA-BFB6 (FE00 retd@BFB4 +2 verified); caller BDA0; RSBX/SSBX ST1 + LD *ar2+ + BCD BFB7 + XOR DP+0x43 + STL DP+0x68; HYPOTHESIS.
; ORIGIN 0xBFAA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6de
	rsbx   st1,ovm
	ssbx   st1,sxm
	ssbx   st1,frct
	ld     *ar2+,a
	bcd    0xbfb7,aneq
	xor    0x43,a
	stl    a,0x68
	retd
	st     #0,*ar2-
