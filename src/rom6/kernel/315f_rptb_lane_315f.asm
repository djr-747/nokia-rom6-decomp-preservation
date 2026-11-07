; ROM6 0x315F RPTB_LANE_315F -- 26w (dark-gap wave-13).
; Evidence: Post-branch head (prev b 2e64); no exterior refs, entry unconfirmed. Bound 315F-3178 (stm; stm; rptb 316A sweep; rpt/mvdd fill; bitf; nop; nop; xc 2,tc (window skips rpt+mvdd exactly); call 2e2f; b opcode @3177 (operand @3178 in-span, 649d split precedent)). C intent in 315f_rptb_lane_315f.c. Recombine-clean.
; ORIGIN 0x315F
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1,brc
	stm    #9551,ar4
	rptb   0x316a
	ldu    *ar2+%,a
	stl    a,-8,*ar4+
	and    #255,a
	stl    a,*ar4+
	rpt    #30
	mvdd   *ar2+0%,*ar4+
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	call   0x2e2f
	b      0x2e64
