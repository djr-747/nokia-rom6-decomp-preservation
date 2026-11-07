; ROM6 0x3538 COND_COPY_3538 -- 31w (dark-gap wave-13).
; Evidence: Post-branch head (prev b 2e64); interior bc 3545 (alt). Bound 3538-3556 (ldm; add; sfta; sub; bc 3545,alt; rpt *(0x8) mvdd lane; call 2e2f; bitf; ccd 93CE (delay stm runs first); b-tail 2e64 @354E; dead tail 3550-3556 mvmm/call 8413/call 2e2f/b past unconditional b, noted). C intent in 3538_cond_copy_3538.c. Recombine-clean.
; ORIGIN 0x3538
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar4,b
	add    #1,b,a
	sfta   a,-1
	sub    #1,a
	bc     0x3545,alt
	stm    #12032,ar3
	rpt    *(0x8)
	mvdd   *ar2+0%,*ar3+
	call   0x2e2f
	bitf   *(0x20ff),#512
	ccd    0x93ce,tc
	stm    #12032,ar2
	b      0x2e64
	mvmm   ar4,ar5
	call   0x8413
	call   0x2e2f
	b      0x2e64
