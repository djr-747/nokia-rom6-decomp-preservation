; ROM6 0x7A5B FRAG_7A5B -- 86w, symbols.yaml data_word.
; Evidence: Bound 7A5B-7AB0 (85w; exit BD F273@7AAC->7AB1 + operand/delays 7AAD-7AAF, end pc+3; FRAG_7AB1 head at 7AB1, tail-1w 7AB0 absorbed — branches @7A5D/7A60->7AB0 interior-ized; exit sc
; ORIGIN 0x7A5B
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvkd   0x253f,*ar3
	b      0x7ab0
	mvdd   *ar4,*ar3
	b      0x7ab0
	bitf   *ar2,#8
	bcd    0x7ab0,ntc
	stm    #9784,ar2
	ld     *ar2,a
	bc     0x7aa8,aneq
	mar    *ar0+
	cmpm   *(0x250f),#34
	bc     0x7aa2,ntc
	cmpm   *(0x34bf),#1
	bc     0x7a90,tc
	cmpm   *(0x34bf),#4
	bc     0x7a90,tc
	stm    #9782,ar3
	stm    #9535,ar4
	sub    *ar3,*ar4,a
	cmpm   *(0x34bf),#3
	xc     2,alt
	addm   #1,*ar3
	xc     2,agt
	addm   #-1,*ar3
	bc     0x7a90,tc
	sub    *ar3,*ar4,a
	bc     0x7a8e,aneq
	b      0x7aa8
	stm    #13502,ar3
	stm    #13514,ar4
	sub    *ar3,*ar4,a
	nop
	nop
	xc     2,alt
	addm   #1,*ar3
	xc     2,agt
	addm   #-1,*ar3
	sub    *ar3,*ar4,a
	bc     0x7aa0,aneq
	b      0x7aa8
	sub    *ar3,*ar4,a
	addm   #1,*ar3
	xc     2,agt
	addm   #-2,*ar3
	ld     #12,b
	sub    *ar2,b
	addm   #1,*ar2
	bd     0x7ab1
	xc     1,bleq
	stl    b,*ar2
	mar    *ar0+
