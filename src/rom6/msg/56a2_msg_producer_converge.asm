; ROM6 0x56A2 MSG_PRODUCER_CONVERGE -- 21w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x56A2
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x3ec8),#16
	bc     0x56b0,ntc
	ld     #137,a
	ld     *(0x589),b
	and    #-32768,b
	sftl   b,-7
	or     b,a
	stlm   a,ar2
	xc     2,ntc
	stm    #137,ar2
	calld  0x2d5e
	stm    #2157,ar3
	ret
