; ROM6 0x379F PORT_LANE_379F -- 33w (dark-gap wave-13).
; Evidence: Pool: ssbx st1,intm has no C form (hardware state). Post-branch head (prev b 2e64); interior bc 37C0 (join next span). Bound 379F-37BF (ld; and; ssbx; portr pa2; bc aeq; st; st; and; nop; portw pa2; nop; portr pa55; or; nop; portw pa55; b-tail 37D3 @37BE). No exterior refs; entry unconfirmed. Recombine-clean.
; ORIGIN 0x379F
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2+%,a
	and    #1,a
	ssbx   st1,intm
	portr  2,*(0xb)
	bc     0x37c0,aeq
	st     #0,*(0x548)
	st     #1,*(0x549)
	and    #32767,b
	nop
	portw  *(0xb),2
	nop
	portr  55,*(0xb)
	or     #16,b
	nop
	portw  *(0xb),55
	b      0x37d3
