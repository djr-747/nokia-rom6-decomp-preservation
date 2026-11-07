; ROM6 0x6A1E SUB_6A1E -- 88w, symbols.yaml data_word.
; Evidence: Bound 6A1E-6A75 (exit F073@6A74->6A83 + operand 6A75); callers F074 @5CFC/5D0C/5D1B (objdump- verified call 0x6a1e x3); bcd FA20@6A3B->6D47 is BCD-conditional per catalog (fall-thr
; ORIGIN 0x6A1E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	pshm   ar7
	stm    #96,ar5
	stm    #9361,ar3
	cmpm   *(0x250f),#34
	bc     0x6a38,ntc
	bitf   *(0x3490),#1
	bc     0x6a31,ntc
	stm    #13494,ar3
	bitf   *(0x3490),#2
	bc     0x6a38,ntc
	stm    #13496,ar3
	bitf   *(0x2512),#128
	bcd    0x6d47,ntc
	ld     *ar3+,16,b
	or     *ar3-,b
	stm    #9806,ar1
	stm    #9358,ar2
	cmpm   *(0x250f),#34
	bcd    0x6a5c,ntc
	stm    #9360,ar4
	bitf   *(0x3490),#1
	bc     0x6a53,ntc
	stm    #13444,ar2
	stm    #13457,ar4
	bitf   *(0x3490),#2
	bc     0x6a5c,ntc
	stm    #13452,ar2
	stm    #13458,ar4
	bc     0x6af9,beq
	bitf   *ar1,#256
	bc     0x6af9,tc
	bitf   *(0x3ec8),#32
	dsub   *(0x3e92),b
	bc     0x6a9c,bleq
	dld    *ar2,a
	bc     0x6a7b,ntc
	ld     *ar4,b
	sub    #1,b
	bc     0x6a76,blt
	stl    b,*ar4
	sfta   a,-3
	dst    a,*ar2
	b      0x6a83
