; ROM6 0x853B FANOUT26_853B -- 26w (overlap-split wave-12).
; Evidence: Bound 853B-8554 (entry stm #4,ar0; banz loop 8541-854D x(10+1 overshoot); tail calls 855F/85FD; exit ret @8554). 4 callers F074 @8505/8526/8538/855C (lane tails, objdump-verified). Interior 0x855F x2/0x8577/0x85E4/0x85FD. Re-homed from mis-origin draft 8554_fanout26_853b.asm (whose bytes duplicated ret@8554 + 8555 + 855F-head, owned elsewhere; deleted). C intent in 853b_fanout26_853b.c. Recombine-clean.
; ORIGIN 0x853B
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #4,ar0
	mvmm   ar4,ar1
	mar    *ar1+0
	stm    #10,ar0
	call   0x855f
	mvmm   ar4,ar2
	mvmm   ar1,ar3
	call   0x8577
	call   0x85e4
	mvmm   ar1,ar2
	mvmm   ar4,ar3
	call   0x8577
	mar    *ar6+
	banz   0x8541,*ar0-
	call   0x855f
	call   0x85fd
	ret
