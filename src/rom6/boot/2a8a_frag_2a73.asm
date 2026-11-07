; ROM6 0x2A8A FRAG_2A73 -- 66w, symbols.yaml data_word.
; Evidence: Bounds 2A73-2A89 + 2A8A-2ACB (exit bd F273@2A86->2979 + operand/delays 2A87-2A89 [end=pc+3]; seg2 exit F073@2ACA->2979 + operand 2ACB; TRIMMED from single 2A73-2ACB draft: bd is UN
; ORIGIN 0x2A8A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b8
	nop
	portw  *ar2+,48
	nop
	nop
	portw  *ar3+,49
	nop
	nop
	portw  *ar3+,50
	nop
	nop
	portw  *ar2,4
	rpt    #20
	nop
	mvdk   *ar2+,0x58e
	cmpm   *ar3(0xffff),#16768
	bc     0x2ac0,ntc
	ld     #0,a
	ldu    *(0x3f00),a
	subs   *ar3(0xfffe),a
	bc     0x2ab2,aneq
	mar    *+ar3(0xfffe)
	dld    *(0x3f04),a
	dst    a,*ar3
	b      0x2abd
	ldu    *(0x3f02),a
	subs   *ar3(0xfffe),a
	bc     0x2ac0,aneq
	mar    *+ar3(0xfffe)
	dld    *(0x3f06),a
	dst    a,*ar3
	mar    *ar2-
	addm   #50,*ar2-
	ld     *(0x13d0),a
	and    #-2,a
	bc     0x2979,aneq
	mvmd   ar2,0x265e
	mvmd   ar3,0x2660
	b      0x2979
