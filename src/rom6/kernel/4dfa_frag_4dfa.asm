; ROM6 0x4DFA FRAG_4DFA -- 105w, symbols.yaml data_word.
; Evidence: Bound 4DFA-4E62 (105w, exit F073@4E61->4E8D + operand); post-BD-delay head, zero refs; head 7719 0004 7213 264B; interior RPTBDs, F074 4348@4E39, RPTB@4E4E, F84C->4E63; F495 = nop
; Pool: 40-bit sfta chain (sfta b,12 on 32-bit B overflows 40-bit; wave-19o rule) + MPYA with caller-live T + sth b,asm on 40-bit B (4EBC long-long class) + BK-circular +0% stepping (base unbound); in-block bc-to-REA/call exits are end-comparator-deterministic (oracle repeat_block.c) for a future author; stays .asm, bytes verified.
; ORIGIN 0x4DFA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #4,bk
	mvdm   0x264b,ar3
	stm    #4,ar1
	ldm    ar1,a
	sub    #1,a
	stlm   a,brc
	ld     #0,b
	bitf   *(0x3eb5),#512
	bc     0x4e17,ntc
	bitf   *(0x586),#2
	bc     0x4e17,ntc
	mvdm   0x261f,ar0
	nop
	mar    *ar3-0%
	banz   0x4e17,*ar0
	mar    *+ar0(0x4)
	rptbd  0x4e2c
	stm    #12032,ar2
	ld     *ar3+%,a
	bitf   *(0x3eb5),#512
	bc     0x4e2b,ntc
	bitf   *(0x586),#2
	bc     0x4e2b,ntc
	banz   0x4e2b,*ar0-
	ld     #0,a
	stm    #0,ar0
	stl    a,*ar2+
	max    b
	ldm    ar1,a
	sub    #1,a
	stlm   a,brc
	stm    #12065,ar4
	stl    b,*ar4
	rptbd  0x4e3b
	stm    #12032,ar2
	ld     *ar2,16,a
	call   0x4348
	stl    a,*ar2+
	ld     #0,a
	popm   al
	sub    #4,a,b
	bc     0x4e63,bneq
	stm    #12032,ar4
	stm    #12160,ar3
	ld     *(0x16),asm
	stm    #3,ar7
	stm    #5,ar5
	stm    #18,brc
	rptb   0x4e59
	ld     *ar3,16,b
	sfta   b,12
	sfta   b,8
	sfta   b,-8
	sfta   b,-11
	ld     #1,16,a
	add    b,a
	mpya   *ar4+
	sth    b,asm,*ar3+
	mar    *+ar4(0xffed)
	banz   0x4e4c,*ar5-
	mar    *ar4+
	banz   0x4e4a,*ar7-
	b      0x4e8d
