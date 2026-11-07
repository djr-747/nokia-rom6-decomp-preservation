; ROM6 0x955F FRAG_955F -- 15w, symbols.yaml data_word.
; Evidence: Bound 955F-956D (15w; exit BD F273@956A->9667 + operand/delays 956B-956D, end pc+3 (9667 = FRAG_ 9667 head); exit scan clean); entries bc F84D@9557->955F byte-verified (from FRAG_9
; ORIGIN 0x955F
	.sect ".text"
	.mmregs
	.global _start
_start:
	bc     0x95a2,ntc
	bitf   *ar2,#1024
	ld     #2,b
	nop
	xc     1,tc
	ld     #4,b
	stl    b,*(0x21fe)
	ld     #0,a
	bd     0x9667
	orm    #128,*ar2
