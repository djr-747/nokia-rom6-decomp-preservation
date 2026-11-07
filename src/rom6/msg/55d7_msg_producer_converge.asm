; ROM6 0x55D7 MSG_PRODUCER_CONVERGE -- 24w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x55D7
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #15,t
	bitt   *ar1
	ld     #12,a
	ld     #25,b
	xc     2,tc
	ld     #25,a
	ld     #12,b
	stl    b,*(0x2652)
	stl    a,*(0x2653)
	ld     *ar1,16,a
	stm    #13,t
	mpya   a
	stl    a,*(0x2651)
	add    #12,a
	stl    a,*(0x2640)
	b      0x5683
