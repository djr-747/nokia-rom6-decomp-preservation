; ROM6 0x3683 BIT_LANE_3683 -- 14w (dark-gap wave-13).
; Evidence: Post-branch head (prev b 2e64); no exterior refs, entry unconfirmed. Bound 3683-3690 (bitf; stm; ld #0; xc 1,tc; ld; stl; call 2e2f; b-tail 2e64 (dead 368F call 5b2 past it noted); falls into 3691 frag (dead past b, noted)). C intent in 3683_bit_lane_3683.c. Recombine-clean.
; ORIGIN 0x3683
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar2,#1
	stm    #15050,ar4
	ld     #0,a
	xc     1,tc
	ld     *ar2+0%,a
	stl    a,*ar4
	call   0x2e2f
	b      0x2e64
	call   0x5b2
