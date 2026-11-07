; ROM6 0xA2B9 MSG_PRIMITIVE_A2B9 -- 10w, symbols.yaml data_word.
; Evidence: 10-word shared tail 1095 4A15 F4E3 8A15 F495 6085 00FF F820 A2B9; RET FC00 @0xA2C2; ~20 F274/F074 callers incl A2A9/AF6F-B355 range (count reported, first-FC00 verified). Bound A2B
; ORIGIN 0xA2B9
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar5+,a
	pshm   ar5
	cala   a
	popm   ar5
	nop
	cmpm   *ar5,#255
	bc     0xa2b9,ntc
	ret
