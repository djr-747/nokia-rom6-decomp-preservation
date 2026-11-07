; ROM6 0x90E7 WRAP_90E7 -- 17w -- overlap-split wave-12.
; Evidence: Pool: ssbx/rsbx st1,c16/cpl have no C form; bcd loop flagged. Bound 90E7-90F7 (call 676; rsbx-cpl; ld #0,dp; ssbx; call 9146; call 90F8; bcd 90EC; rsbx; ssbx; ret @90F7). Assembled from 90e6 tail + 90f7 head-ret (both twins deleted; their dups owned here/by 90F8). Recombine-clean.
; ORIGIN 0x90E7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x676
	rsbx   st1,cpl
	ld     #0,dp
	ssbx   st1,c16
	call   0x9146
	call   0x90f8
	ld     0x61,a
	bcd    0x90ec,agt
	addm   #-1,0x61
	rsbx   st1,c16
	ssbx   st1,cpl
	ret
