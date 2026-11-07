; ROM6 0x87D3 ROUTINE_87D3 -- 22w, symbols.yaml data_word.
; Evidence: Bound 87D3-87E8 (22w; TRIMMED from 87D3-8820 draft at first-outside retd FE00@87E8 — retd is an exit per convention, ordered-scan rule; Bound 87E9-87EA (RETD@87E8 delay slots — wav
; ORIGIN 0x87D3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x590
	stm    #4570,ar3
	ld     #8,a
	rpt    #15
	add    *ar3+,a
	sfta   a,-4
	ld     a,b
	exp    b
	bc     0x87e2,beq
	ld     #22,b
	mac    #-1,b
	sfta   a,-5
	nop
	xc     1,blt
	ld     #0,b
	neg    b
	stlm   b,t
	retd
