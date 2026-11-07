; ROM6 0x9004 KERNEL_9004 -- 62w, symbols.yaml data_word.
; Evidence: Entry F074 060A F7B7 RPTBD ACS block; BOUND CONFIRMED entry-linear (interior 0x900E FC00 is operand trap, not exit); first-RET FC00 @0x9041 len 62; 2x F074 @91DE/920A (task-claimed
; Wave-12: exit ret @9041 owned here; mis-origin twin 9041_kernel_9004.asm deleted (its header described THIS function; its bytes were ret@9041 + 9042-func + 9070-head, now owned here/by 9042/by 9070).
; ORIGIN 0x9004
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x60a
	ssbx   st1,c16
	mvdm   0x1a,ar2
	ld     *ar7,t
	stm    #6,brc
	pshm   ar2
	ld     #-512,a
	stl    a,*ar1+
	stl    a,*ar1-
	rptbd  0x9025
	stm    #12480,ar2
	dsubt  *ar2+,b
	dadd   *ar5,b,a
	drsub  *ar5+,b
	cmps   a,*ar3+
	cmps   b,*ar4+
	stl    a,*ar6+
	stl    b,*ar6-
	max    a
	ld     *ar1,16,b
	max    a
	sth    a,*ar1+
	ld     *ar6+,a
	ld     *ar6-,b
	max    a
	ld     *ar1,b
	max    a
	stl    a,*ar1-
	dsubt  *ar2+%,b
	dadd   *ar5,b,a
	drsub  *ar5+%,b
	cmps   a,*ar3+0%
	cmps   b,*ar4+0%
	stl    a,*ar6+
	stl    b,*ar6-
	max    a
	ld     *ar1,16,b
	max    a
	sth    a,*ar1+
	ld     *ar6+,a
	ld     *ar6-,b
	max    a
	ld     *ar1,b
	max    a
	stl    a,*ar1-
	ld     *ar1+,a
	sub    *ar1-,a
	popm   ar2
	add    #2,a
	banzd  0x9009,*ar2-
	sfta   a,-1
	stl    a,*ar7+
	rsbx   st1,c16
	ret
