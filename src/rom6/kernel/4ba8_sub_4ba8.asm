; ROM6 0x4BA8 SUB_4BA8 -- 47w, symbols.yaml data_word.
; Evidence: Entry F074; bound 4BA8-4BD6 (exit F073@4BD5->4D9C + operand); 4x ext callers (survey objdump- verified); interior calld 4D9D (SUB_4D9D coexists as callee); ends adjacent FILL_2F5D_
; ORIGIN 0x4BA8
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stl    a,*(0x2f1f)
	stl    b,*(0x2f1e)
	sub    #64,a,b
	bc     0x4bd7,bneq
	stm    #128,ar2
	stm    #12160,ar3
	rpt    #77
	mvdd   *ar2+,*ar3+
	calld  0x9268
	stm    #12162,ar3
	ld     #-9,asm
	calld  0x4d9d
	stm    #2,brc
	calld  0x4f3a
	andm   #127,*ar2
	calld  0x4ee0
	stm    #1,brc
	call   0x51d8
	bc     0x4d9c,bneq
	stm    #14,ar5
	stm    #128,ar4
	calld  0x2c88
	stm    #12123,ar3
	b      0x4d9c
