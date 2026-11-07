; ROM6 0xDFCF PORT_DISPATCH_DFCF -- 47w, symbols.yaml data_word.
; Evidence: Entry F074 0682 4A06 4A07 4A16; caller F074 @AA2A verified; first exit ret FC00 @DFFD; interior bc beq DFDC->DFE6 cond + calld DC43/DC2E/DFFE; HYPOTHESIS.
; ORIGIN 0xDFCF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x682
	pshm   st0
	pshm   st1
	pshm   ar6
	stm    #1856,st1
	stm    #0,bk
	ld     *(0xc4c),b
	and    #1,b
	bc     0xdfe6,beq
	ld     *(0xc4c),b
	and    #-2,b
	calld  0xdc43
	stl    b,*(0xc4c)
	calld  0xdc2e
	stm    #3476,ar4
	stm    #159,brc
	rptbd  0xdff2
	stm    #3476,ar2
	ld     *ar2,-3,a
	stl    a,3,*ar2+
	ld     #0,dp
	stm    #79,brc
	calld  0xdffe
	stm    #3474,ar2
	popm   ar6
	popm   st1
	popm   st0
	ret
