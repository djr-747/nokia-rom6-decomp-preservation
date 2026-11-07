; ROM6 0xB12F FRAG_B12F -- 18w, symbols.yaml data_word.
; Evidence: Bound B12F-B140 (18w, exit FC00@B140); bacc-table arm (table B129-B12E of DISPATCH_B11C); shared mvdk-22D idiom with AF6A leaves; HYPOTHESIS.
; ORIGIN 0xB12F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	mvdk   *(0x22d),0x265b
	call   0xa3c5
	call   0xa3e1
	call   0xa4de
	cc     0xa91c,beq
	calld  0xa2b9
	stm    #-8685,ar5
	ret
