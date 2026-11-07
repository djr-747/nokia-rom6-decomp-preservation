; ROM6 0x3CD2 PORT4850_SEQ -- 73w, symbols.yaml data_word.
; Pool: min a (E06A precedent, wave-12). MIN_ACC has a catalog row (0xF487) but no leaf; the min/max ladder also gates the xc-skip windows (ssbx/rsbx st0,tc have no C form per the hardware-state rule, so the TC feed is uncarriable). Joint blockers: macar t,b,a, mvdk-to-ST1 (0x12) lane. Otherwise groundable: bitf/bc chain, ld-16 shifts, sub/and/or ladder, portw pa41.
; Evidence: Entry F074 0638; bound 3CD2-3D1A; callers F074@3DB2/3DC4/3DF2 + F274@2413/2543; portw pa41/48/49/50/4; HYPOTHESIS.
; ORIGIN 0x3CD2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x638
	bitf   *(0x51f),#128
	bc     0x3cde,ntc
	bitf   *(0x263b),#4
	b      0x3cdf
	ssbx   st0,tc
	ld     *(0x3e94),16,b
	xc     2,ntc
	ld     *(0x3edc),16,b
	min    a
	ld     *(0x3e96),16,b
	stm    #16021,ar2
	bc     0x3cef,tc
	ld     *(0x3edf),16,b
	stm    #16093,ar2
	rsbx   st0,tc
	sub    a,b
	bc     0x3cf5,bgeq
	ssbx   st0,tc
	sub    *ar2,16,a
	stm    #21845,t
	ld     *(0x263b),b
	and    #4,b
	stm    #1140,ar2
	xc     2,beq
	stm    #1180,ar2
	ld     *(0x12),16,b
	macar  t,b,a
	mvdk   *(0x9),0x12
	ld     *ar2,a
	and    #1023,a
	ld     #0,b
	xc     1,tc
	ld     #1,b
	bc     0x3d13,bneq
	ld     #-4097,b
	and    b,a
	b      0x3d16
	ld     #4096,b
	or     b,a
	nop
	portw  *(0x8),41
	ret
