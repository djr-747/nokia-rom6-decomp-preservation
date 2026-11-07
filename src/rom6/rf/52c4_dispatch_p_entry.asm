; ROM6 0x52C4 DISPATCH_P_ENTRY -- 51w, symbols.yaml data_word.
; Evidence: Entry F074 059C; bound 52C4-52F6 (exit F073@52F5->5315); sole external caller F074@51FA objdump- verified (call 0x52C4); leads P-lane fan; HYPOTHESIS.
; ORIGIN 0x52C4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	bitf   *(0x2627),#8
	bc     0x56b9,ntc
	st     #0,*(0x263e)
	andm   #-1025,*(0x2512)
	bitf   *(0x3ec8),#16
	bc     0x52e2,ntc
	stm    #1417,ar2
	andm   #32767,*ar2
	ld     *(0x589),b
	and    #16384,b
	bc     0x52e2,beq
	orm    #-32768,*ar2
	bitf   *(0x2549),#4
	bc     0x52f7,ntc
	stm    #2340,ar1
	ld     *ar1-,a
	and    #31,a
	stm    #1326,t
	stlm   a,ah
	mpya   a
	add    *ar1,a
	subs   *(0x2479),a
	bc     0x56b9,aneq
	b      0x5315
