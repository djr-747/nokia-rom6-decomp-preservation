; ROM6 0x7EB1 BACC_7EB3 -- 11w (overlap-split wave-12).
; Pool: bacc a (F4E2). Computed branch via A (loaded from *AR3 at entry -- runtime target, unbound statically; pool per the 5C4F cala rule). Words 7EB1-7EB2 are the 7EA7 span's retd delay slots (xor b,a; sth a,*ar4- execute under 7ea7's retd, then return -- cross-span delay convention per the D581 precedent; also this file's leading words).
; Evidence: Fall-through entry frag_7EB3 at 0x7EB3 (HYPOTHESIS: no in-span caller; direct-entry shape after the delay words). Runs dark helper_0594 (call); A += -20141 (add #lk, F000 B153); AR3 = A-low (stlm a,ar3, STLM MMR-direct row, AR3 routing known); settle nops; A = *AR3 (ld); computed branch (bacc). Bound 7EB1-7EBB, ends with the bacc (no fall-through).
; ORIGIN 0x7EB1
	.sect ".text"
	.mmregs
	.global _start
_start:
	xor    b,a
	sth    a,*ar4-
	call   0x59e
	add    #-20141,a
	stlm   a,ar3
	nop
	nop
	ld     *ar3,a
	bacc   a
