; ROM6 0x8643 CALL_LANE_8643 -- 11w (dark-gap wave-13).
; Evidence: Post-call head (prev 8641 call 592); no exterior refs, entry unconfirmed. Bound 8643-864D (calls 8BD5/8F97/8813/8653/8675; ret @864D). C intent in 8643_call_lane_8643.c. Recombine-clean.
; ORIGIN 0x8643
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x8bd5
	call   0x8f97
	call   0x8813
	call   0x8653
	call   0x8675
	ret
