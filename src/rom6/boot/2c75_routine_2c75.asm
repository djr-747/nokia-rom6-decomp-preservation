; ROM6 0x2C75 ROUTINE_2C75 -- 19w, symbols.yaml data_word.
; Evidence: Bound 2C75-2C87 (13w; exit RET FC00@2C87 byte-verified, exit scan clean); entry call F074@40-> 2C75 byte-verified (from block30 uploaded code, head-exact; call-only entry, pre-word
; ORIGIN 0x2C75
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #0,*(0x866)
	st     #0,*(0x54c)
	portr  2,*(0x8)
	and    #-3,a
	nop
	portw  *(0x8),2
	orm    #516,*(0x0)
	ret
