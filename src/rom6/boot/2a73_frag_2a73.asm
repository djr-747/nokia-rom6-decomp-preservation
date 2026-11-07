; ROM6 0x2A73 FRAG_2A73 -- 23w, symbols.yaml data_word.
; Evidence: Bounds 2A73-2A89 + 2A8A-2ACB (exit bd F273@2A86->2979 + operand/delays 2A87-2A89 [end=pc+3]; seg2 exit F073@2ACA->2979 + operand 2ACB; TRIMMED from single 2A73-2ACB draft: bd is UN
; ORIGIN 0x2A73
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvdm   0x265e,ar2
	mvdm   0x2660,ar3
	mar    *ar2+
	nop
	portw  *ar3+,49
	nop
	nop
	portw  *ar3+,50
	mvmd   ar3,0x2660
	nop
	portw  *ar2+,4
	rpt    #11
	nop
	bd     0x2979
	mvmd   ar2,0x265e
