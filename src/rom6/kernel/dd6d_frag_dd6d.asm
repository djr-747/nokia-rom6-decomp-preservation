; ROM6 0xDD6D FRAG_DD6D -- 10w, symbols.yaml data_word.
; Evidence: Bound DD6D-DD76 (10w; exit retd FE00@DD74 + delays DD75-DD76 absorbed (F495 440B); exit scan clean); post-RET head only (FC00@DD6C, zero ext refs); HYPOTHESIS.
; ORIGIN 0xDD6D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+,16,a
	sub    *(0xec7),16,a
	mpya   b
	add    #3,b
	add    *ar2,b
	retd
	nop
	ld     0x0b,16,a
