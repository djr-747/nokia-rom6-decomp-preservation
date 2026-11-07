; ROM6 0xB0A1 FRAG_B0A1 -- 28w, symbols.yaml data_word.
; Evidence: Bound B0A1-B0BC (28w, exit FC00@B0BC); F073-entry head (branch-joined); HYPOTHESIS.
; ORIGIN 0xB0A1
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	fcalld 0x1a8fd
	stm    #12074,ar3
	fcall  0x1a260
	call   0xa679
	call   0xa5e1
	cmpm   *(0x2510),#192
	bc     0xb0b8,ntc
	ld     *(0x2efe),a
	bc     0xb0b8,aneq
	fcall  0x180a7
	call   0xa7b7
	call   0xa7eb
	ret
