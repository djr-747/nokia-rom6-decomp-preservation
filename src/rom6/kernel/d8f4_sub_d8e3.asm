; ROM6 0xD8F4 SUB_D8E3 -- 2w, symbols.yaml data_word.
; Evidence: Entry 7669 3214 7712 0B6A; first exit retd FE00 @D8F3 +delays 8059 805A (survey 0xD9C6 shrunk, critic-confirmed); caller F274 @D979 calld verified; Bound D8F4-D8F5 (RETD@D8F3 delay
; ORIGIN 0xD8F4
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    a,0x59
	stl    a,0x5a
