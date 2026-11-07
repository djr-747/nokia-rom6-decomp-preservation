; ROM6 0x96BD MEAS_RSSI_POSTER -- 67w, symbols.yaml data_word.
; Evidence: Called from 0x942B/0x94A5/0x995C; STM AR2,#96 + PORTR PA2 measurement read gated by *(0x20FF) BITF lanes; LDU *(0x20FB) - *(0x587) threshold compare with BC 0x9700 ALT; posts measu
; ORIGIN 0x96BD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5c6
	stm    #8447,ar4
	bitf   *ar4,#1
	bcd    0x970b,ntc
	stm    #96,ar2
	portr  2,*ar2
	bitf   *ar2,#256
	rc     ntc
	bitf   *ar4,#2
	bc     0x96ec,ntc
	ldu    *(0x20fb),a
	sub    *(0x587),a
	bc     0x9700,alt
	ld     *(0x20fd),a
	bc     0x96dc,aeq
	b      0x9704
	ssbx   st1,intm
	portr  54,*ar2
	orm    #1,*ar2
	nop
	portw  *ar2,54
	nop
	portr  2,*ar2
	orm    #512,*ar2
	nop
	portw  *ar2,2
	ssbx   st1,intm
	st     #256,*ar2
	nop
	portw  *ar2,1
	rpt    #20
	nop
	andm   #-2049,*ar4
	portr  2,*ar2
	andm   #-257,*ar2
	nop
	portw  *ar2,2
	call   0x97dd
	rete
