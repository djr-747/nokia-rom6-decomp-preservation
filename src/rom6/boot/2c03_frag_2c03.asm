; ROM6 0x2C03 FRAG_2C03 -- 114w, symbols.yaml data_word.
; Evidence: Bound 2C03-2C74 (exit F073@2C73->283D + operand 2C74); entry bc F84C@283B (byte-verified); post-B head; RE-LABELED from SUB (zero F074 callers whole-ROM, critic role-fix); interior
; ORIGIN 0x2C03
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x650
	st     #-32768,*ar2
	nop
	portw  *ar2,1
	rpt    #20
	nop
	rsbx   st1,sxm
	portr  55,*(0xb)
	bitf   *(0xb),#128
	and    #7680,b
	sub    #3072,b,a
	nop
	nop
	xc     2,agt
	ld     #3072,b
	sftl   b,-9
	sub    #6,b
	abs    b
	ld     b,2,a
	sub    b,a
	sub    #10,a
	ld     *(0x8),asm
	ld     #19,16,b
	or     #14984,b
	ld     b,asm,a
	and    #1792,a
	stm    #96,ar2
	stl    a,*ar2
	stm    #1353,ar3
	bc     0x2c6e,ntc
	andm   #-1823,*ar3
	orm    #1,*ar3
	ld     *(0x548),a
	sub    #16724,a,b
	bc     0x2c6e,beq
	sub    #24948,a,b
	bc     0x2c6e,beq
	andm   #-2,*ar3
	ld     a,-8,b
	xor    a,b
	and    #128,b
	bc     0x2c64,beq
	ld     *ar3,b
	bitf   *(0x8),#32
	bc     0x2c57,tc
	bitf   *(0x8),#128
	bc     0x2c5c,tc
	b      0x2c60
	bitf   *(0x8),#128
	bc     0x2c60,tc
	or     #8,b
	b      0x2c6f
	or     #4,b
	b      0x2c6f
	ld     *ar3,b
	bitf   *(0x8),#128
	bc     0x2c6f,ntc
	or     #12,b
	b      0x2c6f
	ld     *ar3,b
	or     *ar2,b
	or     #32,b
	stl    b,*ar3
	b      0x283d
