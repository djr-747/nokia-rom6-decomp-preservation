; ROM6 0x35BB XC_LANE_35BB -- 10w (dark-gap wave-13).
; Evidence: Post-branch head (prev b 2e64); no exterior refs, entry unconfirmed. Bound 35BB-35C4 (ld; stm; andm; xc 2,agt (A>0 runs orm + ret); ret (conditional); fall-through untaken joins 35C5 frag). C intent in 35bb_xc_lane_35bb.c. Recombine-clean.
; ORIGIN 0x35BB
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x11),a
	stm    #1309,ar1
	andm   #-2081,*ar1
	xc     2,agt
	orm    #2080,*ar1
	ret
