; ROM6 0xA9E9 FRAG_A9E9 -- 70w, symbols.yaml data_word.
; Evidence: Bound A9E9-AA2E (68w; exit RET FC00@AA2E byte-verified, exit scan otherwise clean — F981 FCALLs correctly ignored as non-exits/non-entries per rule: F981@36F5/3758->AA2C + F981@5C6
; ORIGIN 0xA9E9
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x686
	bitf   *(0x263a),#512
	rc     tc
	ld     *(0xb67),a
	rc     aneq
	bitf   *(0x51c),#3
	rc     tc
	ld     *(0x51c),a
	and    #3072,a
	sub    #2048,a
	bc     0xaa1b,aeq
	call   0x68a
	call   0x9fcf
	st     #12854,*(0x337c)
	call   0xc5f9
	bitf   *(0x2b08),#3
	bc     0xaa13,ntc
	bitf   *(0x577),#4096
	ccd    0xbcfc,tc
	stm    #12854,ar1
	call   0xa109
	call   0x9df4
	calld  0xab78
	stm    #12854,ar2
	bitf   *(0x51e),#4096
	stm    #3148,ar2
	andm   #-5,*ar2
	xc     2,tc
	orm    #4,*ar2
	stm    #12854,ar1
	rpt    #159
	mvdk   *ar1+,0xd94
	call   0xdfcf
	call   0xcf01
	ret
