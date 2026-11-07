; ROM6 0x8F7A ROUTINE_8F7A -- 29w, symbols.yaml data_word.
; Evidence: Bound 8F7A-8F96 (29w; exit RET FC00@8F96 byte-verified, exit scan clean); entries 8x calld F274@ 8B4B/8B62/8B7C/8B91/8D3C/8D59/8D77/8D90->8F7A byte-verified + post-RET head (FC00@8
; ORIGIN 0x8F7A
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #7,brc
	rptbd  0x8f95
	ld     *ar2,16,a
	bit    *ar2+,0
	abs    a
	sub    0x00,16,a,b
	bc     0x8f8d,blt
	sub    0x01,16,a,b
	bc     0x8f91,blt
	and    #-4,16,a
	bd     0x8f92
	sfta   a,-2,b
	add    0x02,16,b
	bd     0x8f92
	sfta   a,1,b
	nop
	add    0x00,16,a,b
	xc     1,tc
	neg    b
	bit    *ar2,0
	st     b,*ar2 || ld     *ar2+,a
	ret
