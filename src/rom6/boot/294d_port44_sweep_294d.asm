; ROM6 0x294D PORT44_SWEEP_294D -- 29w (dark-gap wave-13).
; Evidence: Post-branch head (prev b 283D); no exterior refs, entry unconfirmed. Bound 294D-2969 (call 72E; stm/brc/stm; rptb 2968 sweep loop with interior bc 295F; rpt/nop; ret @2969). C intent in 294d_port44_sweep_294d.c. Recombine-clean.
; ORIGIN 0x294D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x72e
	stm    #29,brc
	stm    #10457,ar3
	ld     #3,b
	rptb   0x2968
	nop
	portw  *(0xb),44
	nop
	nop
	portw  *ar3+,45
	nop
	portr  45,*(0x9)
	and    #4096,16,a
	bc     0x295f,aneq
	rpt    #30
	nop
	nop
	ret
