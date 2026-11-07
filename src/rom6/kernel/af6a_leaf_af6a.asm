; ROM6 0xAF6A LEAF_AF6A -- 10w, symbols.yaml data_word.
; Evidence: Entry AF6A (AF64-AF69 jtab of SELECTOR_DISPATCH_AF57, consumer bacc; AF64-AF69 bytes verified, untouched); bound AF6A-AF73 (exit FC00@AF73); JTAB_AF57_6WAY leaf; shared leaf idiom 
; ORIGIN 0xAF6A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	mvdk   *(0x22d),0x265b
	calld  0xa2b9
	stm    #-8881,ar5
	ret
