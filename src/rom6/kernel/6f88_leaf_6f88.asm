; ROM6 0x6F88 LEAF_6F88 -- 41w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 6F88-6FB0; callers F074 6C08 + F274 6F3A; 0x2512/0x51F-gated 0x3E97/0x3EDC select; HYPOTHESIS.
; ORIGIN 0x6F88
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	stm    #16020,ar4
	bitf   *(0x51f),#128
	bc     0x6f9f,ntc
	ld     *(0x2611),b
	sub    #124,b
	bc     0x6f9f,bleq
	ld     *(0x2611),b
	sub    #975,b
	bc     0x6f9f,bgeq
	stm    #16092,ar4
	xc     1,alt
	ld     #0,a
	sub    *ar4,16,a,b
	stm    #5461,t
	xc     1,bgt
	ld     *ar4,16,a
	mpya   a
	sfta   a,2
	add    #16384,1,a
	st     #0,*(0x8)
	stm    #3,t
	mpya   a
	ret
