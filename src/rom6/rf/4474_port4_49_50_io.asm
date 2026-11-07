; ROM6 0x4474 PORT4_49_50_IO -- 50w, symbols.yaml data_word.
; Evidence: Entry 69F8 13D0 0400 orm *(0x13D0); first-RET FC00 @0x44A5; zero F-refs; ports pa4/pa49/pa50 + BITF 61F8 13D0 0400 + call 4479->3EE1; entry mechanism unproven; HYPOTHESIS port io.
; ORIGIN 0x4474
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #1024,*(0x13d0)
	pshd   *(0x263a)
	call   0x3ee1
	add    #10,a
	sub    #4999,a,b
	andm   #-97,*(0x263a)
	stm    #0,ar6
	xc     1,bgt
	ld     #10,a
	portr  4,*(0xb)
	nop
	portw  *ar4,49
	nop
	nop
	portw  *(0x13),50
	nop
	nop
	portw  *(0x8),4
	rpt    #22
	nop
	bitf   *(0x13d0),#1024
	bc     0x4498,tc
	popd   *(0x263a)
	nop
	portw  *(0xb),4
	rpt    #22
	nop
	ret
