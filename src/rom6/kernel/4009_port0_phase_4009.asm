; ROM6 0x4009 PORT0_PHASE_4009 -- 76w, symbols.yaml program_word.
; Evidence: Fall-through from 4007 port0 txn (prev span); pshm al/ah/ag, INTM guard, pa0 strobe + rpt settle, 3EB5 poll with aeq/aneq forks, 40A1 poll loop, pa45 retry, andm/portw lane, rc/rsbx/ret; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x4009
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   al
	pshm   ah
	pshm   ag
	bitf   *(0x7),#2048
	ssbx   st1,intm
	portr  0,*(0x8)
	or     #12,a
	nop
	portw  *(0x8),0
	rpt    #22
	nop
	ld     *(0x3eb5),a
	and    #2,a
	bc     0x403d,aeq
	sub    #7,b,a
	bc     0x4030,aneq
	popm   ag
	popm   ah
	popm   al
	nop
	nop
	portw  *(0x8),40
	pshm   al
	pshm   ah
	pshm   ag
	pshm   bl
	pshm   bh
	pshm   bg
	ld     #13,b
	call   0x40a1
	and    #3,a
	bc     0x4033,aneq
	popm   bg
	popm   bh
	popm   bl
	portr  45,*(0x9)
	and    #4096,16,a
	bc     0x403d,aneq
	popm   ag
	popm   ah
	popm   al
	nop
	nop
	portw  *(0x8),45
	and    #-17,b
	nop
	portw  *(0xb),44
	rc     tc
	rsbx   st1,intm
	ret
