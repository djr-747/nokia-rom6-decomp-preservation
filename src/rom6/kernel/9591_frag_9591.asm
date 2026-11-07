; ROM6 0x9591 FRAG_9591 -- 17w, symbols.yaml data_word.
; Evidence: Bound 9591-95A1 (17w; exit BD F273@959E->9667 + operand/delays 959F-95A1, end pc+3; exit scan clean); entries bc F84B@9575->9591 + bc F830@958D->959D mid-span byte-verified (both i
; ORIGIN 0x9591
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar2,#1536
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
