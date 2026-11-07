; ROM6 0xA74C SUB_A74C -- 84w, symbols.yaml data_word.
; Evidence: Post-RET head F074 065E; interior CALLs 8A08/877D/864E/8821; first exit retd FE00 @A79D +2 thru A79F; bound A74C-A79F; zero inbound; HYPOTHESIS.
; ORIGIN 0xA74C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65e
	cmpm   *(0x2510),#193
	rc     ntc
	call   0x8a08
	call   0x877d
	bitf   *(0x51c),#3
	bc     0xa7a0,tc
	stm    #1308,ar2
	bitf   *ar2,#256
	bc     0xa76b,ntc
	andm   #-769,*ar2
	call   0x864e
	stm    #1308,ar2
	andm   #-13,*ar2
	orm    #8,*ar2
	call   0x8821
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	bc     0xa798,aeq
	calld  0x8a54
	stm    #12694,ar2
	call   0x9df4
	calld  0xbbef
	stm    #12694,ar2
	calld  0x9fcf
	stm    #10380,ar6
	call   0xa12b
	calld  0x9f42
	stm    #159,brc
	calld  0x6a2
	stm    #12694,ar2
	calld  0xbadb
	stm    #12694,ar2
	bitf   *(0x51c),#2048
	ccd    0xbac2,ntc
	stm    #12694,ar2
	stm    #1308,ar2
	bitf   *ar2,#8
	rc     ntc
	retd
	andm   #-13,*ar2
