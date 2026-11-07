; ROM6 0x40A1 PORT45_POLL -- 27w, symbols.yaml program_word.
; Evidence: PORTR pa45 poll loop at 0x40B4 (AND 4096, BNEQ), pa44 write, RPT-14 wait. Called from PORT0_TXN phases. Bound 40A1-40BB (wave-5: exit RET FC00@40BB + post-RET head byte-verified; 6
; ORIGIN 0x40A1
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x652
	portr  45,*(0x9)
	and    #4096,16,a
	bc     0x40a3,aneq
	or     #16,b
	nop
	portw  *(0xb),44
	rpt    #14
	nop
	b      0x40b4
	portr  45,*(0x8)
	and    #4096,a,b
	bc     0x40b4,bneq
	ret
