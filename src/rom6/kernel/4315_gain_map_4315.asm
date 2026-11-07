; ROM6 0x4315 GAIN_MAP_4315 -- 51w, symbols.yaml data_word.
; Evidence: Entry F074 0606 + BITF 61F8 3EC8 0020 + 61F8 263B 0004; first-RET FC00 @0x4347; 2 callers 6BAC 756F; internal bd 433F->4345; HYPOTHESIS gain map.
; ORIGIN 0x4315
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x606
	bc     0x4330,aleq
	sub    #32,a,b
	bc     0x4327,blt
	exp    a
	ld     #25,b
	norm   a
	sfta   a,-9
	sfta   a,-16
	sub    *(0xe),b
	and    #63,a
	xc     1,blt
	ld     #0,b
	stlm   b,t
	add    #-20322,a
	stlm   a,ar3
	mpy    #1541,b
	sfta   b,13
	add    *ar3,16,b,a
	bitf   *(0x3ec8),#32
	bc     0x4343,ntc
	bitf   *(0x263b),#4
	ld     #1140,b
	xc     2,ntc
	ld     #1180,b
	add    *ar2,b
	stlm   b,ar2
	bd     0x4345
	ld     *ar2,16,b
	nop
	ld     *ar2,16,b
	sfta   b,6
	neg    b
	add    a,b
	ret
