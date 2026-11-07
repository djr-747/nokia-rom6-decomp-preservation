; ROM6 0x56DE PORTXACT_ENTRY -- 30w, symbols.yaml data_word.
; Evidence: Code entry 56DE-56FB (first exit ret FC00 @56FB, only conditional bc @56EA inside): ld *(0x2658),b, ssbx/rsbx intm, portr pa16, portw pa14; 2 objdump-verified F074 callers @0x554E 
; ORIGIN 0x56DE
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x2658),b
	add    b,a
	ssbx   st1,intm
	ld     *(0x53b),b
	add    a,b
	stl    b,*(0x53b)
	st     #-1,*(0x557)
	bc     0x56ef,aeq
	portr  16,*(0x557)
	add    #4999,a
	nop
	portw  *(0x8),14
	rpt    #14
	nop
	st     #0,*(0x2658)
	rsbx   st1,intm
	ret
