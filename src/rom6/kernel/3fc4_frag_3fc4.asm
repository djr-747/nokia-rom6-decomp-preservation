; ROM6 0x3FC4 FRAG_3FC4 -- 54w, symbols.yaml data_word.
; Evidence: Bound 3FC4-3FF9 (54w; exit B F073@3FF8->3FBA + operand 3FF9 — branch-tailed backward into bounded 3EBE-3FC3; exit scan otherwise clean); post-RET head only (FC00@3FC3 RF-program sw
; ORIGIN 0x3FC4
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #640,*ar2
	nop
	portw  *ar2,43
	ld     #11,b
	ld     #640,a
	call   0x4007
	ld     #0,a
	ld     #10,b
	call   0x4007
	ld     #2048,a
	ld     #13,b
	call   0x4007
	stm    #16014,ar3
	nop
	portw  *ar3,37
	stm    #16015,ar3
	nop
	portw  *ar3,38
	st     #510,*ar2
	nop
	portw  *ar2,17
	rpt    #16
	nop
	ld     #2432,a
	bitf   *(0x3ec8),#2048
	bc     0x3fba,tc
	portr  12,*(0xb)
	or     *(0x3ecc),b
	nop
	portw  *(0xb),12
	b      0x3fba
