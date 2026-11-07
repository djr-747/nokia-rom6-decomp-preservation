; ROM6 0x3988 INTM_IDLE_3988 -- 22w (dark-gap wave-13).
; Evidence: Pool: ssbx/rsbx st1,intm + idle have no C form (hardware state). Bound 3988-399D (post-call head after 3986 call; ssbx; andm; bitf; bc 3997,tc; portw pa15; rpt/nop; rsbx; idle; ssbx; bitf; bc opcode @399D (operand @399E owned by 399e span, 649d/649f split precedent; bare word). No known callers; entry unconfirmed. Untaken-399D path executes the operand word (decode unconfirmed, flagged). Recombine-clean.
; ORIGIN 0x3988
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,intm
	andm   #-3,*(0x263a)
	bitf   *(0x2639),#512
	bc     0x3997,tc
	nop
	portw  *(0x8),15
	rpt    #6
	nop
	rsbx   st1,intm
	idle   1
	ssbx   st1,intm
	bitf   *(0x263a),#2
	; @399D f820 bc 0x3997,ntc opcode (operand @399E in 399E span)
	.word 0xF820 ; bc opcode
