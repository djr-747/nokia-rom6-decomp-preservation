; ROM6 0xAC22 FRAG_AC22 -- 42w, symbols.yaml data_word.
; Evidence: Bound AC22-AC4B (42w; exit RET FC00@AC4B byte-verified, exit scan clean); entry bccnd F844@ABE3-> AC22 byte-verified (cond, pre-head exterior); interior join F073@AC3A->AC41 in-spa
; ORIGIN 0xAC22
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,1,a
	stlm   a,ar0
	addm   #-1,*ar4
	bitf   *(0x3ec8),#64
	nop
	nop
	sub    #1024,a,b
	bc     0xac3c,ntc
	stm    #3562,ar4
	bc     0xac41,blt
	sub    #1950,a
	stm    #2886,ar4
	xc     2,ageq
	stm    #1862,ar4
	b      0xac41
	stm    #3560,ar4
	xc     2,bgeq
	stm    #2786,ar4
	bitf   *(0x3ec8),#16
	mar    *ar4+0
	mvdd   *ar2,*ar4+
	ld     *ar3,a
	xc     1,tc
	sfta   a,-3
	add    *ar4,a
	stl    a,*ar4
	ret
