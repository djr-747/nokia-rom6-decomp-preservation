; ROM6 0x90D6 WRAP_90D6 -- 17w -- overlap-split wave-12.
; Evidence: Pool: ssbx/rsbx st1,c16/cpl have no C form; bcd loop flagged. Bound 90D6-90E6 (call 676; rsbx-cpl; ld #0,dp; ssbx; call 9118; call 90F8; bcd 90DB; rsbx; ssbx; ret @90E6). Re-homed from ret-first twin 90d5_wrap_90b9.asm (deleted; exit ret @90D5 owned by 90B9). Recombine-clean.
; ORIGIN 0x90D6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x676
	rsbx   st1,cpl
	ld     #0,dp
	ssbx   st1,c16
	call   0x9118
	call   0x90f8
	ld     0x61,a
	bcd    0x90db,agt
	addm   #-1,0x61
	rsbx   st1,c16
	ssbx   st1,cpl
	ret
