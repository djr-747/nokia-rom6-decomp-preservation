; ROM6 0x569E MSG_PRODUCER_CONVERGE -- 4w, symbols.yaml program_word.
; Evidence: CORRECTED per critic K3: RPTBD@54B5 + RET@54BA belong to 0x54A4 body, not 0x54BB. Proper body is the J1+J convergence chain, bounds 54BB-54F7 + 54F8-5502 + 5503-55B0 + 55B1-55D6 + 
; ORIGIN 0x569E
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,*(0x264e)
	call   0x77ee
