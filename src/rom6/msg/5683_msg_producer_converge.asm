; ROM6 0x5683 MSG_PRODUCER_CONVERGE -- 23w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x5683
	.sect ".text"
	.mmregs
	.global _start
_start:
	orm    #1,*(0x2628)
	ld     *(0x264e),a
	or     #1,a
	and    #-5,a
	cmpm   *(0x2476),#6
	bc     0x569a,tc
	cmpm   *(0x2476),#7
	bc     0x569c,tc
	or     #16,a
	b      0x569e
