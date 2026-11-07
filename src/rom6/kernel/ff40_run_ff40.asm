; ROM6 0xFF40 RUN_FF40 -- 33w (overlap-split wave-12).
; Evidence: Bound FF40-FF60 (head stm/stm; interior calls FF69 x2 + FF5E x2; idle lane; ret @FF60). Interior entries FF5E (rpt/nop lane, callers @FF54/FF5B interior-only) + FF61 (E724, owned by ff61 span) + FF69 (owned by ff69 span) documented, words owned there. Former tail FF61-FF77 duplicated ff61/ff69 spans (owned there; deleted from this file). Recombine-clean.
; ORIGIN 0xFF40
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1918,bk
	stm    #129,ar2
	call   0xff69
	stm    #4095,bk
	stm    #4096,ar2
	call   0xff69
	stlm   b,ar0
	ld     #0,b
	rpt    0x19
	lms    *ar3,*ar2+
	stm    #-134,ar4
	stm    #11,ar2
	call   0xff5e
	abdst  *ar2,*ar4
	sth    a,*(0x1001)
	mvmd   ar0,0x1000
	call   0xff5e
	idle   2
	rpt    #6
	nop
	ret
