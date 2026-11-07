; ROM6 0x54F8 MSG_PRODUCER_CONVERGE -- 11w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x54F8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,a
	or     #256,a
	bitf   *(0x2512),#256
	bc     0x5502,tc
	and    #-257,a
	stl    a,*ar3
