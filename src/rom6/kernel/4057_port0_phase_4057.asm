; ROM6 0x4057 PORT0_PHASE_4057 -- 74w, symbols.yaml program_word.
; Evidence: Fall-through from 4055 port0 txn phase2 (prev span); pshm bl/bh/bg, INTM guard, pa0 strobe + rpt settle, 3EB5 poll, b-tail/call forks into 40A1 poll lanes, and/or/sub lane, rsbx/ret; interior b/bc joins; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x4057
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   bl
	pshm   bh
	pshm   bg
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
	bc     0x4073,aneq
	call   0x40a1
	b      0x4095
	pshm   bl
	pshm   bh
	pshm   bg
	ld     #13,b
	call   0x40a1
	and    #3,a
	bc     0x4076,aneq
	popm   bg
	popm   bh
	popm   bl
	nop
	pshm   bl
	pshm   bh
	pshm   bg
	call   0x40a1
	ld     #13,b
	call   0x40a1
	and    #12,a
	nop
	sub    #12,a
	bc     0x4086,aneq
	popm   bg
	popm   bh
	popm   bl
	call   0x40a1
	and    #2048,a,b
	bc     0x409b,beq
	or     #-4096,a
	popm   bg
	popm   bh
	popm   bl
	rc     tc
	rsbx   st1,intm
	ret
