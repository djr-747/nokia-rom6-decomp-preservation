; ROM6 0xDA21 FRAG_DA21 -- 17w, symbols.yaml data_word.
; Evidence: Bound DA21-DA31 (25w; exit retd FE00@DA2F + delays DA30-DA31 included per convention; exit scan clean); post-RET head only (FE00@DA20, zero ext refs); remainder DA32-DA47 (24w) sta
; ORIGIN 0xDA21
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #7,0x58
	ld     0x58,16,a
	bc     0xda35,aneq
	stl    a,0x59
	ld     #4,a
	and    0x5a,a
	bc     0xda32,aeq
	st     #24,0x5a
	st     #28801,0x5c
	retd
	st     #26968,0x5d
