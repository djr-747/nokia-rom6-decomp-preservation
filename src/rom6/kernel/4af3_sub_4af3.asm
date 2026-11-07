; ROM6 0x4AF3 SUB_4AF3 -- 19w, symbols.yaml data_word.
; Evidence: Entry F074; bound 4AF3-4B05 (exit F073@4B04 self-loop + operand 4B05); caller F274@4ABA (byte- verified calld 0x4af3, gap-internal); cond cc->4AF3@4AA7 documented by survey; HYPOTH
; ORIGIN 0x4AF3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	cmpm   *(0x250f),#34
	bc     0x4b07,ntc
	ssbx   st1,intm
	portr  56,*(0xb)
	and    #8,b
	bc     0x4b06,beq
	rsbx   st1,intm
	idle   1
	b      0x4af3
