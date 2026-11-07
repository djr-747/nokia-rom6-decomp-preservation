; ROM6 0xDA48 SUB_DA48 -- 54w, symbols.yaml data_word.
; Evidence: Entry 7714 007A 10F8 0B68; first exit retd FE00 @DA7D (interior b @DA75 lands interior); caller F274 @D7B8 verified; HYPOTHESIS.
; ORIGIN 0xDA48
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #122,ar4
	ld     *(0xb68),a
	and    #4,a
	sfta   a,-2
	add    *(0x79),1,a
	add    #-9773,a
	and    #-1,a
	reada  *ar4
	ld     #1,a
	and    0x60,a
	bcd    0xda65,aeq
	addm   #1,0x5f
	ld     #-9768,a
	add    *ar4,a
	and    #-1,a
	reada  0x60
	b      0xda75
	rsbx   st0,tc
	ld     *ar4,a
	sub    #3,a,b
	bcd    0xda6f,bneq
	add    #-9764,a
	bitf   0x60,#128
	and    #-1,a
	reada  0x60
	xc     2,tc
	orm    #256,0x60
	bitf   0x60,#1
	bc     0xda80,ntc
	st     #0,0x62
	st     #23,0x61
	retd
