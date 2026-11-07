; ROM6 0x4E63 FRAG_4E63 -- 51w, symbols.yaml data_word.
; Evidence: Bound 4E63-4E95 (51w, exit FC00@4E95); branch-entry F84C@4E40 (objdump bc); zero callers; interior join 4E8D<-B; head F110 0006 + F272 4E8C + F274 4F5F@4E91 (out-call to existing S
; Pool: 40-bit sfta chain (sfta b,12 on 32-bit B; wave-19o rule) + MPYA *ar4+% with caller-live T and BK-circular stepping + sth b,asm on 40-bit B (4EBC long-long class); stays .asm, bytes verified.
; ORIGIN 0x4E63
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #6,a,b
	bc     0x4e69,bneq
	stm    #8,bk
	sub    #8,a,b
	bc     0x4e96,beq
	sub    #10,a,b
	bc     0x4e79,blt
	stm    #8,bk
	stm    #12034,ar4
	stm    #12038,ar3
	mvdd   *ar4+,*ar3+
	mvdd   *ar4,*ar3
	stm    #12032,ar4
	ld     *(0x16),asm
	stm    #455,brc
	rptbd  0x4e8c
	stm    #12160,ar3
	ld     *ar3,16,b
	sfta   b,12
	sfta   b,8
	sfta   b,-8
	sfta   b,-11
	ld     #1,16,a
	add    b,a
	mpya   *ar4+%
	sth    b,asm,*ar3+
	stm    #12160,ar2
	stm    #1111,ar3
	calld  0x4f5f
	stm    #28,ar1
	ret
