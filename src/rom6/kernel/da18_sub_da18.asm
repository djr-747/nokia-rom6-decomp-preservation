; ROM6 0xDA18 SUB_DA18 -- 9w, symbols.yaml data_word.
; Evidence: Entry F310 0001 FA4C DA23 (8-word tiny routine); first exit retd FE00 @DA20; caller F274 @CF75 verified; sits after DAFD->DB18 fall-through, no call from DAFD; HYPOTHESIS.
; ORIGIN 0xDA18
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #1,b
	bcd    0xda23,bneq
	addm   #1,0x59
	st     #3,0x5a
	retd
