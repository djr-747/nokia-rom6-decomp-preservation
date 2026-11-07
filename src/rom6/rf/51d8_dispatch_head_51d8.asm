; ROM6 0x51D8 DISPATCH_HEAD_51D8 -- 52w, symbols.yaml data_word.
; Evidence: Entry F074 059C + bitf *(0x2F5C),#-256 + bcd 0x51E6; first-RET FC00 @0x520B; 1 caller 0x4BC9 via F074; body calls 0x57FE/0x52C4/0x573B/0x520C/0x57A3; HYPOTHESIS dispatch head.
; ORIGIN 0x51D8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	bitf   *(0x2f5c),#-256
	bcd    0x51e6,ntc
	stm    #1295,ar2
	ld     *ar2,a
	sub    #2,a
	ld     #1,b
	rc     ageq
	bc     0x51f1,tc
	pshm   bl
	pshm   bh
	pshm   bg
	ld     #2,b
	call   0x70a
	popm   bg
	popm   bh
	popm   bl
	retd
	ld     #0,b
	stl    b,*ar2
	calld  0x425f
	stm    #2322,ar2
	call   0x57fe
	call   0x52c4
	call   0x573b
	call   0x520c
	ld     *(0x250f),a
	and    #240,a
	cmpm   *(0x8),#32
	cc     0x5755,ntc
	call   0x57a3
	ret
