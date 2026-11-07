; ROM6 0x355C STORE_LANES_355C -- 68w, symbols.yaml program_word.
; Evidence: Fall-through from 3557 frag (prev span); orm/mvmm lane preset, aeq-fork AR presets, bitf/xc guarded orm lanes, ld/shift-mask/store lanes, b-tail into next span 35A0; no exterior callers, entry unconfirmed, flagged.
; ORIGIN 0x355C
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #4,*(0x54f)
	mvmm   ar2,ar3
	ld     *ar2,a
	and    #8,a
	stm    #9490,ar4
	stm    #9536,ar0
	stm    #9535,ar5
	stm    #13514,ar6
	bc     0x3575,aeq
	stm    #9545,ar4
	stm    #9591,ar0
	stm    #9590,ar5
	stm    #13515,ar6
	bitf   *ar2,#1
	ld     *ar2+%,-8,b
	and    #255,b
	bc     0x3583,ntc
	bc     0x3582,aeq
	orm    #512,*(0x54f)
	stl    b,*ar0
	bitf   *ar3,#4
	bc     0x35b7,ntc
	bc     0x358c,aeq
	orm    #16,*(0x54f)
	ld     *ar4,b
	bitf   *ar3,#2
	and    #-257,b
	xc     2,tc
	or     #256,b
	stl    b,*ar4
	ld     *ar2,-8,b
	and    #255,b
	stl    b,*ar5
	ld     *ar2+%,b
	and    #255,b
	stl    b,*ar6
	b      0x35b7
