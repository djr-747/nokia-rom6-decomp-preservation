; ROM6 0xD8E3 SUB_D8E3 -- 17w, symbols.yaml data_word.
; Evidence: Entry 7669 3214 7712 0B6A; first exit retd FE00 @D8F3 +delays 8059 805A (survey 0xD9C6 shrunk, critic-confirmed); caller F274 @D979 calld verified; Bound D8F4-D8F5 (RETD@D8F3 delay
; ORIGIN 0xD8E3
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #12820,0x69
	stm    #2922,ar2
	rptz   a,#153
	stl    a,*ar2+
	stm    #3086,ar2
	rpt    #9
	stl    a,*ar2+
	stm    #3076,ar2
	rpt    #9
	mvkd   0xfb9c,*ar2+
	retd
