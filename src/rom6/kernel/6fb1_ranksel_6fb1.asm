; ROM6 0x6FB1 RANKSEL_6FB1 -- 41w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 6FB1-6FD9; callers F074 6BE4/A40D(ext) + F274 6F1A; *ar3(4-8) sub-ladder 6FE3/0D20 + bcd 6FD7; HYPOTHESIS.
; ORIGIN 0x6FB1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	sub    *ar3(0x4),a,b
	bcd    0x6fd7,bleq
	ld     #3,b
	nop
	sub    *ar3(0x5),a,b
	bcd    0x6fd7,bleq
	ld     #4,b
	nop
	sub    *ar3(0x6),a,b
	bcd    0x6fd7,bleq
	ld     #5,b
	nop
	sub    *ar3(0x7),a,b
	bcd    0x6fd7,bleq
	ld     #6,b
	nop
	sub    *ar3(0x8),a,b
	bcd    0x6fd7,bleq
	ld     #7,b
	nop
	ld     #8,b
	ld     b,a
	popm   ar3
	ret
