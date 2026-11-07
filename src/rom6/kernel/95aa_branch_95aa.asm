; ROM6 0x95AA BRANCH_95AA -- 14w (dark-gap wave-13).
; Evidence: Post-bacc head (prev bacc b @95A9); no exterior refs, entry unconfirmed. Bound 95AA-95B7 (st; and; and; sub; bc 95B8,beq (join next span); ld #0; b-tail 9667 @95B6-95B7). C intent in 95aa_branch_95aa.c. Recombine-clean.
; ORIGIN 0x95AA
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #0,*(0x20fa)
	and    #-256,a
	and    #-513,a,b
	sub    #7168,b
	bc     0x95b8,beq
	ld     #0,a
	b      0x9667
