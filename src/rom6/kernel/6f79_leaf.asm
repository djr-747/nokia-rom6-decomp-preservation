; ROM6 0x6F79 LEAF_6F79 -- 15w, call+rpt/stl fills, ret.
; ORIGIN 0x6F79
	.sect ".text"
	.mmregs
	.global _start
_start:
	call 0x5b4
	stm #985,ar2
	ld #128,a
	rpt #31
	stl a,*ar2+
	stm #9364,ar2
	ld #0,a
	rpt #31
	stl a,*ar2+
	rpt #63
	stl a,*ar2+
	ret
