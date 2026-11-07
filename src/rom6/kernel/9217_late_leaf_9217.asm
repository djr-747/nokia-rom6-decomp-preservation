; ROM6 0x9217 LATE_LEAF_9217 -- 28w, symbols.yaml data_word.
; Evidence: Entry F074 0594 7313 0060 7710 0009 7713 3218; first-RET @0x9232 (len 28); 6 callers 924E 926A 9283 92A0 92BD 92D9 (all F074); HYPOTHESIS late-stage leaf.
; ORIGIN 0x9217
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	mvmd   ar3,0x60
	stm    #9,ar0
	stm    #12824,ar3
	stm    #12800,ar5
	stm    #12816,ar4
	stm    #32,bk
	ld     #-512,a
	rpt    #31
	stl    a,*ar5+
	stm    #12800,ar5
	ld     #0,a
	stl    a,*ar5
	stm    #12834,ar2
	stm    #12160,ar7
	mvmm   ar7,ar6
	ret
