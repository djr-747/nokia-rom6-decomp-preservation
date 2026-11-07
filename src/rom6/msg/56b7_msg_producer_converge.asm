; ROM6 0x56B7 MSG_PRODUCER_CONVERGE -- 6w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x56B7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x56a2
	ld     #0,a
	call   0x56de
	ret
