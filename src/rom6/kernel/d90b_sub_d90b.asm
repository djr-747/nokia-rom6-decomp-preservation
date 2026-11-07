; ROM6 0xD90B SUB_D90B -- 84w, symbols.yaml data_word.
; Evidence: Entry 7719 0000 F074 0684 (0x0684 zeros caveat); first exit ret FC00 @D95E (interior bd @D949 interior); caller F074 @A978 verified; HYPOTHESIS.
; ORIGIN 0xD90B
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,bk
	call   0x684
	pshm   st1
	stm    #1856,st1
	ld     #22,dp
	bcd    0xd91f,aneq
	andm   #-3,0x68
	bitf   0x68,#1
	bc     0xd91f,ntc
	calld  0xd95f
	stm    #17,brc
	ld     #22,dp
	ld     #3,a
	and    0x68,a
	sub    #3,a
	bc     0xd92e,aneq
	ld     #96,dp
	mvdm   0x300a,ar2
	ld     #8,a
	bd     0xd949
	rpt    #159
	stl    a,*ar2+
	ld     #96,dp
	stm    #12355,ar1
	calld  0xd798
	stm    #12311,ar3
	ld     #96,dp
	mvdm   0x300a,ar5
	calld  0xd5d6
	st     #12311,0x13
	ld     #96,dp
	mvdm   0x300a,ar2
	stm    #159,brc
	rptbd  0xd948
	ld     #-8,16,b
	ld     *ar2,16,a
	sfta   a,1
	and    b,a
	sth    a,*ar2+
	ld     #22,dp
	bitf   0x68,#1
	bc     0xd957,tc
	stm    #12355,ar2
	ld     *ar2+,a
	bc     0xd957,aneq
	calld  0xd95f
	stm    #56,brc
	ld     #2,a
	and    0x68,a
	andm   #-2,0x68
	cc     0xd970,aneq
	popm   st1
	ret
