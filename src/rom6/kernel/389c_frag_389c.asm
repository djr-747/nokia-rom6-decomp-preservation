; ROM6 0x389C FRAG_389C -- 45w, symbols.yaml data_word.
; Evidence: Bound 389C-38C8 (41w; exit RET FC00@38C8 byte-verified, exit scan clean of BD/BACC/FE00/F073); entry B F073@AE85->389C byte-verified (far uncond ref, AE-arm zone) + interior join F
; ORIGIN 0x389C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x62c
	bitf   *(0x3ec8),#2
	bc     0x3943,tc
	bitf   *(0x51f),#128
	bc     0x3913,tc
	ld     *(0x3e80),b
	add    b,a
	bitf   *(0x3e7e),#2
	cc     0x38fb,tc
	bitf   *(0x3e7e),#4
	cc     0x38c9,tc
	cmpm   *(0x12),#49
	bc     0x38c5,ntc
	nop
	portw  *(0x8),49
	nop
	nop
	portw  *(0x9),50
	mar    *+ar2(0x2)
	xc     2,ntc
	stl    a,*ar2+
	sth    a,*ar2+
	ret
