; ROM6 0x94F0 HEAD_94F0 -- 62w, symbols.yaml data_word.
; Evidence: Entry F074 05D4 7712 021E; bound 94F0-952D (exit F273 bd@952A->283D OUT + delays 952B-952D; F273 unconditional per catalog); fall-through after FC00@94EF (COBBA_VERIFY_LOOP end); i
; ORIGIN 0x94F0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5d4
	stm    #542,ar2
	st     #1024,*ar2
	nop
	portw  *ar2,1
	rpt    #22
	nop
	portr  2,*ar2
	orm    #1024,*ar2
	andm   #-513,*ar2
	nop
	portw  *ar2,2
	nop
	portr  0,*ar2
	orm    #16,*ar2
	nop
	portw  *ar2,0
	rpt    #22
	nop
	portr  54,*ar2
	andm   #-2,*ar2
	nop
	portw  *ar2,54
	orm    #1,*(0x20ff)
	orm    #4096,*(0x552)
	bitf   *(0x20ff),#128
	bc     0x9529,ntc
	portr  12,*(0xb)
	or     *(0x3eca),b
	nop
	portw  *(0xb),12
	ld     #0,a
	bd     0x283d
	stl    a,*(0x20fb)
