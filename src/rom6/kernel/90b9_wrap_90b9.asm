; ROM6 0x90B9 WRAP_90B9 -- 29w -- overlap-split wave-12.
; Evidence: Pool: ssbx/rsbx st1,c16 have no C form; nested banz loops flagged. Bound 90B9-90D5 (call 676; ssbx; call 9118; pshm/stm x3; rptb 90CB inner + banz 90C3; mar/mar; popm; banz 90BC outer; rsbx; ret @90D5). Carved from 90b8 giant (deleted; its head ret @90B8 kept as 1w abut). Recombine-clean.
; ORIGIN 0x90B9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x676
	ssbx   st1,c16
	call   0x9118
	pshm   ar7
	stm    #12576,ar7
	stm    #3,ar2
	stm    #7,brc
	rptb   0x90cb
	ld     *ar7+,t
	dadst  *ar5,a
	dsadt  *ar5+%,b
	cmps   a,*ar4+%
	cmps   b,*ar3+%
	st     trn,*ar6+
	banz   0x90c3,*ar2-
	mar    *ar4+0%
	mar    *ar3+0%
	popm   ar7
	banz   0x90bc,*ar1-
	rsbx   st1,c16
	ret
