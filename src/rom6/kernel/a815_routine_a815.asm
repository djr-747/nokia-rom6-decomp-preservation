; ROM6 0xA815 ROUTINE_A815 -- 46w, symbols.yaml data_word.
; Evidence: Bound A815-A842 (46w; exit RET FC00@A842 byte-verified, exit scan clean of BD/BACC/F073); entries 2x cc F94D@AFCC + F944@B05B->A815 byte-verified (CC = cond call per op_cc mask FF8
; ORIGIN 0xA815
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x67c
	cmpm   *(0x2510),#192
	rc     ntc
	bitf   *(0x51c),#3
	bc     0xa830,tc
	bitf   *(0x51f),#6144
	bc     0xa830,tc
	ld     *(0x2efe),a
	rc     aneq
	fcall  0x1811b
	stm    #9593,ar4
	fcalld 0x1a8da
	stm    #12432,ar3
	st     #192,*(0x25a0)
	fcalld 0x1a824
	stm    #9598,ar4
	ld     a,-1,b
	stl    b,*(0x257f)
	sfta   a,15
	andm   #32767,*(0x257e)
	or     *(0x257e),a
	stl    a,*(0x257e)
	ret
