; ROM6 0x68CA SUB_68CA -- 45w, symbols.yaml data_word.
; Evidence: Bound 68CA-68F6 (45w, ret FC00@68F6); caller F074@650F (slice-verified); zero interior calls; HYPOTHESIS.
; ORIGIN 0x68CA
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,b
	ld     *(0x564),a
	bc     0x68f6,aneq
	ld     *(0x565),a
	sub    *ar6,a
	stm    #2325,ar2
	sub    *ar2,a
	bc     0x68f6,agt
	ld     *(0x36d),a
	sub    *(0x250d),a
	ld     *(0x565),b
	xc     2,alt
	add    #1,b
	sub    #2,a
	add    #4,b
	xc     2,ageq
	add    #1,b
	sub    *ar2,b,a
	ld     #1,b
	nop
	xc     1,alt
	ld     #0,b
	bitf   *(0x54f),#1024
	ld     *(0x545),a
	bc     0x68f6,ntc
	xc     1,aeq
	ld     #0,b
	ret
