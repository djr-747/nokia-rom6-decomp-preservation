; ROM6 0xAFBF HEAD_AFBF -- 20w, symbols.yaml data_word.
; Evidence: Entry F074 0678; bound AFBF-AFD2 (20w, exit FC00@AFD2 objdump-verified); interior calls 0678/A2C3/A3C5/A3E1/A4DE + F94D cc A815,beq (conditional call per catalog CC F900/FF80) + ca
; ORIGIN 0xAFBF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x678
	call   0xa2c3
	mvdk   *(0x22d),0x265b
	call   0xa3c5
	call   0xa3e1
	call   0xa4de
	cc     0xa815,beq
	calld  0xa2b9
	stm    #-8760,ar5
	ret
