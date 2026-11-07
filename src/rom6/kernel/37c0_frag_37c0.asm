; ROM6 0x37C0 FRAG_37C0 -- 24w, symbols.yaml data_word.
; Evidence: Bound 37C0-37D7 (24w; exit B F073@37D6->2E64 + operand 37D7, byte-verified; exit scan clean); entry bc F845@37A6->37C0 byte-verified (cond aeq, thin dark-src from unclaimed arm 379
; ORIGIN 0x37C0
	.sect ".text"
	.mmregs
	.global _start
_start:
	or     #-32768,b
	andm   #-33,*(0x549)
	nop
	portw  *(0xb),2
	nop
	portr  55,*(0xb)
	and    #-17,b
	nop
	portw  *(0xb),55
	rsbx   st1,intm
	call   0x2e2f
	b      0x2e64
