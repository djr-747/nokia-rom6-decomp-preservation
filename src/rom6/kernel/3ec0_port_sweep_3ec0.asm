; ROM6 0x3EC0 PORT_SWEEP_3EC0 -- 33w (dark-gap wave-13).
; Evidence: Pool: rsbx st1,intm has no C form (hardware state). Post-portw head; interior bc 3ED8 + join 3ED5. Bound 3EC0-3EE0 (nop/nop/portw/nop/nop/portw/rpt/nop/mvdk/st/bitf/bc/rsbx/ld/nop/portw/rpt/nop/ret @3EE0). No exterior refs; entry unconfirmed. Recombine-clean.
; ORIGIN 0x3EC0
	.sect ".text"
	.mmregs
	.global _start
_start:
	nop
	nop
	portw  *(0xb),50
	nop
	nop
	portw  *(0x8),4
	rpt    #17
	nop
	mvdk   *(0x8),0x58e
	st     #64,*(0x13d0)
	bitf   *(0x51e),#8192
	bc     0x3ed8,tc
	rsbx   st1,intm
	ld     #15000,a
	nop
	portw  *(0x8),10
	rpt    #17
	nop
	ret
