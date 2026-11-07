; ROM6 0xA99A FRAG_A99A -- 17w, symbols.yaml data_word.
; Evidence: Bound A99A-A9AA (17w; exit RET FC00@A9AA byte-verified, exit scan clean); post-RET head (FC00@A999); zero ext refs; no interior calls; chain link; HYPOTHESIS.
; ORIGIN 0xA99A
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #10137,ar2
	rpt    #58
	mvkd   0x3044,*ar2+
	bitf   *(0x51c),#1
	rc     ntc
	ld     *(0x3082),a
	rc     aeq
	ld     #0,a
	rpt    #58
	mvmd   al,0x2799
	ret
