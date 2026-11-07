; ROM6 0x697F DARAM_SAVE_RESTORE -- 8w, stm/mvdd/st, ret.
; ORIGIN 0x697F
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm #1340,ar3
	stm #9748,ar2
	mvdd *ar3,*ar2
	st #0,*ar3
	ret
