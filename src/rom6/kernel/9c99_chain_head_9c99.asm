; ROM6 0x9C99 CHAIN_HEAD_9C99 -- 54w, symbols.yaml data_word.
; Evidence: Words F074 06D4 F074 06BE + RPTBD mpy loop + 2x F074 9F35 @0x9CB2/0x9CBA (both verified); tail 9CCF->9CE7->9D0B; RET FC00 @0x9D15. Bound 9C99-9CCE (wave-6: exit F073@9CCD->9CE7 byt
; ORIGIN 0x9C99
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6d4
	call   0x6be
	stm    #10696,ar2
	ld     *(0x860),a
	stl    a,*ar2+
	stm    #2140,ar3
	stm    #159,brc
	rptbd  0x9cab
	stm    #2140,ar3
	mpy    *ar2,*ar3,a
	sth    a,*ar2+
	ld     #159,b
	bitf   *(0x860),#144
	bc     0x9ccf,ntc
	call   0x9f35
	calld  0x8bde
	stm    #10697,ar4
	call   0x8c0a
	call   0x9f35
	cmpm   *(0x2f03),#0
	andm   #-24577,*(0x860)
	xc     2,ntc
	orm    #16384,*(0x860)
	stm    #12432,ar3
	calld  0x86e3
	stm    #10697,ar4
	ld     #16,b
	b      0x9ce7
