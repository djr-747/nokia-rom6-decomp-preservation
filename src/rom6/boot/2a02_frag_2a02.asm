; ROM6 0x2A02 FRAG_2A02 -- 12w, symbols.yaml data_word.
; Evidence: Bound 2A02-2A0D (12w; exit B F073@2A0C->2A8A + operand 2A0D, byte-verified; exit scan clean); entries bc F820@29E3->2A02 + bcd FA44@29E9->2A02 byte-verified (chained from FRAG_29E1
; ORIGIN 0x2A02
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *ar3,#4096
	bc     0x2a0e,ntc
	st     #16,*ar3
	stm    #4728,ar3
	stm    #4722,ar2
	b      0x2a8a
