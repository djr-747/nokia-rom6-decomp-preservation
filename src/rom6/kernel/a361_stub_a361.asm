; ROM6 0xA361 STUB_A361 -- 66w, symbols.yaml data_word.
; Evidence: Entry F074 0654 F230 8000 FE45 7712 2639; 5x callers F074@AF8A/B054/B0C6/B15E/B348; TRIMMED per res3 byte evidence: interior retd FE00@A3A0 (objdump retd) + delays A3A1-A3A2 end th
; ORIGIN 0xA361
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x654
	and    #-32768,b,a
	rcd    aeq
	stm    #9785,ar2
	ld     *ar2,a
	and    #2048,a
	calld  0x40bc
	andm   #-3073,*ar2
	ssbx   st1,intm
	portr  3,*(0x8)
	and    #-2,a
	nop
	portw  *(0x8),3
	rpt    #17
	nop
	bitf   *(0x3ec8),#32
	bc     0xa39f,ntc
	andm   #-17,*(0x13d0)
	call   0x3ee1
	add    *(0x3ee7),a
	stm    #9719,ar2
	stl    a,*ar2-
	stm    #9730,ar3
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
	rpt    #17
	nop
	mvdk   *ar2+,0x58e
	rsbx   st1,intm
	retd
	ld     #1,a
	nop
