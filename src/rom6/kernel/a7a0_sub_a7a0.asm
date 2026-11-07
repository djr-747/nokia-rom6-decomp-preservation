; ROM6 0xA7A0 SUB_A7A0 -- 23w, symbols.yaml data_word.
; Evidence: Entry 7714 09C8 (stm #2504,ar4); bound A7A0-A7B6 ret; interior calld 86FB @A7A2 + rc @A7AE; inbound bc @A759 + post-retd-delays A79F; HYPOTHESIS.
; ORIGIN 0xA7A0
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #2504,ar4
	calld  0x86fb
	stm    #12432,ar3
	stm    #10137,ar2
	rpt    #75
	mvkd   0x3090,*ar2+
	bitf   *(0x51c),#1
	rc     ntc
	ld     *(0x3082),a
	rc     aeq
	ld     #0,a
	rpt    #75
	mvmd   al,0x2799
	ret
