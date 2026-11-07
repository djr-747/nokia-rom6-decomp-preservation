; ROM6 0xA269 FRAG_A269 -- 67w, symbols.yaml data_word.
; Evidence: Bound A269-A2AB (67w; sole exit RET FC00@A2AB byte-verified); BACC-table arm entry (A255-table slot 3 = A269, table bytes verified); BACC-reached, zero F074/F274 callers whole-imag
; ORIGIN 0xA269
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xa3a3
	rc     bneq
	mvdk   *(0x22d),0x265b
	call   0xa3f0
	call   0xa5c6
	ld     *(0x2615),b
	sub    #3400,b
	bc     0xa281,blt
	call   0xa4de
	call   0xa482
	b      0xa291
	call   0xa482
	ld     *(0x262c),b
	bc     0xa28f,beq
	ld     *(0x2615),b
	sub    #800,b
	bc     0xa28f,blt
	call   0xe64c
	call   0xa4de
	calld  0xa2b9
	stm    #-8787,ar5
	ld     *(0x262c),b
	bcd    0xa2a9,beq
	stm    #-8781,ar5
	ld     *(0x2615),b
	sub    #800,b
	bc     0xa2a9,blt
	ld     *(0x2615),b
	sub    #3400,b
	bc     0xa2a9,bgeq
	stm    #-8780,ar5
	call   0xa2b9
	ret
