; ROM6 0x2A5F FRAG_2A5F -- 20w, symbols.yaml data_word.
; Evidence: Bound 2A5F-2A72 (26w; exit B F073@2A71->2979 + operand 2A72 — branch-tailed backward, first and only exit-class in span; exit scan clean; pre-word 2993 = operand value, not post-RE
; ORIGIN 0x2A5F
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#512
	bc     0x2ac0,ntc
	st     #0,*(0x13d0)
	stm    #96,ar2
	st     #15000,*ar2
	nop
	portw  *ar2,4
	rpt    #20
	nop
	mvdk   *ar2+,0x58e
	b      0x2979
