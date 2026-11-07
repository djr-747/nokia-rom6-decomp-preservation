; ROM6 0x6987 ROUTINE_6987 -- 4w, stm/mvdd, ret.
; ORIGIN 0x6987
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm #9751,ar3
	mvdd *ar2,*ar3
	ret
