; ROM6 0xAE71 SUB_AE71 -- 47w, symbols.yaml program_word.
; Evidence: Bound AE71-AE9F (47w); entry TRACE (same histogram: AE71-AE89 heads x10682, rare AE8E lane x37); dispatch prologue with interior below-floor b-exits (388C/389C) + call 0596 + bc AE
; ORIGIN 0xAE71
	.sect ".text"
	.global _start
_start:
	ld     *(0x260f),a
	b      0x388c
	ld     *(0x260e),a
	b      0x388c
	ld     *(0x2613),a
	bitf   *(0x2628),#512
	bc     0x388c,tc
	bitf   *(0x2629),#4096
	bc     0x388c,tc
	b      0x389c
	call   0x596
	cmpm   *(0x262b),#0
	bc     0xaea0,tc
	ld     *(0x2613),a
	stm    #16128,ar3
	sub    #512,a,b
	bc     0xae9d,blt
	sub    #975,a
	nop
	nop
	xc     2,alt
	stm    #16130,ar3
	mvdd   *ar3+,*ar2+
	mvdd   *ar3+,*ar2+
	ret
