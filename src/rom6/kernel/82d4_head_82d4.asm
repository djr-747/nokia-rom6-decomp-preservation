; ROM6 0x82D4 HEAD_82D4 -- 5w (overlap-split wave-12).
; Pool: rsbx st1,cpl has no C form (hardware state, 8220/ssbx precedent) -- stays .asm.
; Evidence: Bound 82D4-82D8 (rsbx/ld #0,dp/mar/mvmm); function entry with 2 calld callers @82C2 (TRAMP_82B7) + @82CC (SUB_82CB), objdump-verified; falls through into FRAG_82D9 @82D9 (head-frag abut). Carved from 81f1_sub232_810a.asm tail (deleted). Recombine-clean.
; ORIGIN 0x82D4
	.sect ".text"
	.mmregs
	.global _start
_start:
	rsbx   st1,cpl
	ld     #0,dp
	mar    *+ar2(0x7)
	mvmm   ar2,ar1
