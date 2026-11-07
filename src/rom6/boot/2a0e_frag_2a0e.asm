; ROM6 0x2A0E FRAG_2A0E -- 14w, symbols.yaml data_word.
; Evidence: Bound 2A0E-2A1B (14w; exit B F073@2A1A->2AC0 + operand 2A1B, byte-verified (2AC0 = FRAG_2A73-seg2 interior, CODE); exit scan clean); entry bc F820@2A04->2A0E byte-verified (chained
; ORIGIN 0x2A0E
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#16
	bc     0x2a1c,ntc
	ld     #15000,a
	nop
	portw  *(0x8),4
	rpt    #14
	nop
	b      0x2ac0
