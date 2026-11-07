; ROM6 0x2BED FRAG_2BAA -- 22w, symbols.yaml data_word.
; Evidence: Bounds 2BAA-2BEC + 2BED-2C02 (exit F073@2BEB->283D + operand 2BEC; second segment entered via interior forward join F073@2BE2->2BED, exit F073@2C01->283D + operand 2C02); entry bc 
; ORIGIN 0x2BED
	.sect ".text"
	.mmregs
	.global _start
_start:
	portr  56,*(0x8)
	and    #-9,a
	nop
	portw  *(0x8),56
	nop
	portr  2,*(0x8)
	or     #2048,a
	nop
	portw  *(0x8),2
	nop
	b      0x283d
