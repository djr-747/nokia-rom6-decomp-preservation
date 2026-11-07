; ROM6 0x9042 KERNEL_9042 -- 47w -- overlap-split wave-12.
; Evidence: Pool: ssbx/rsbx st1,c16 have no C form (hardware state); dual-accumulate lanes flagged. Bound 9042-9070 (call 60C; ssbx; rptb 906E dadst/dsadt/cmps block + st trn; rsbx; ret @9070). Re-homed from mis-origin twin 9041_kernel_9004.asm (whose header described the 9004-function; deleted). Recombine-clean.
; Wave-12: exit ret @9070 owned here; ret-first twin 9070 (word0) re-homed to 9071 file.
; ORIGIN 0x9042
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x60c
	ssbx   st1,c16
	rptb   0x906e
	ld     *ar7+,16,a
	sub    *ar7,16,a,b
	sth    b,*ar2+
	add    *ar7+,16,a,b
	sth    b,*ar2
	ld     *ar2-,t
	dadst  *ar5,a
	dsadt  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dsadt  *ar5,a
	dadst  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dadst  *ar5,a
	dsadt  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dsadt  *ar5,a
	dadst  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	ld     *ar2,t
	dadst  *ar5,a
	dsadt  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dsadt  *ar5,a
	dadst  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dadst  *ar5,a
	dsadt  *ar5+,b
	cmps   a,*ar4+
	cmps   b,*ar3+
	dsadt  *ar5,a
	dadst  *ar5+%,b
	cmps   a,*ar4+0%
	cmps   b,*ar3+0%
	st     trn,*ar6+
	rsbx   st1,c16
	ret
