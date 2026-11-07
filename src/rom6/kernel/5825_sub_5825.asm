; ROM6 0x5825 SUB_5825 -- 97w, symbols.yaml data_word.
; Evidence: Entry F074 059C; bound 5825-5885 (FC00@5885); caller F074@4823 objdump-verified (call 0x5825); interior uncond b@5850->5875 + b@586D->5875 joins with xc guards; residual frag 5823-
; Pool: cala b@5883 with computed target B = *(AR4-walk) over a runtime-populated key/vector table at 0xDD34+ (even words keys vs A with -1 terminator, odd words vectors; image bytes at 0xDD30-0xDD45 are code, not key/vector pairs, so the table is overlay/RAM state, target unknowable statically; CALA precedent 4AD8). Secondary: bc 0x5875,aeq@582D forks on dark SUB_059C A-out (stored to *(0x60), never rewritten before the test). stays .asm, bytes verified.
; ORIGIN 0x5825
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	pshm   ar0
	st     #0,*(0x2ef5)
	stl    a,*(0x60)
	bc     0x5875,aeq
	cmpm   *(0x2510),#192
	bc     0x5852,ntc
	stl    a,*(0x2620)
	ld     #0,b
	stm    #9759,ar2
	stl    b,*ar2+
	stl    b,*+ar2
	stl    b,*+ar2
	stm    #9805,ar2
	ld     *(0x914),a
	sub    *(0x2ef8),a
	stl    b,*ar2
	sub    #8,a,b
	xc     2,aeq
	st     #2,*ar2
	sub    #17,a
	xc     2,beq
	st     #2,*ar2
	xc     2,aeq
	st     #2,*ar2
	b      0x5875
	cmpm   *(0x2510),#177
	bc     0x5834,tc
	stl    a,*(0x2620)
	ld     #0,b
	stm    #9758,ar2
	stl    b,*ar2+
	stl    b,*ar2+
	stl    b,*+ar2
	stl    b,*+ar2
	cmpm   *(0x250f),#34
	bc     0x586f,ntc
	ld     *(0x352c),b
	stl    b,*(0x264c)
	add    #114,b
	stl    b,*(0x264d)
	b      0x5875
	st     #11036,*(0x264c)
	st     #11150,*(0x264d)
	ld     *(0x2f02),a
	stm    #-8909,ar4
	mar    *ar4+
	cmpm   *ar4,#-1
	sub    *ar4+,a,b
	bc     0x5884,tc
	bc     0x5879,bneq
	ld     *ar4,b
	cala   b
	popm   ar0
	ret
