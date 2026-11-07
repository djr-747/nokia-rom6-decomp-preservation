; ROM6 0x9281 SUB_9281 -- 29w, symbols.yaml data_word.
; Evidence: Bound 9281-929D (29w; exit RET FC00@929D); entry F074 0594; caller F274@0x4BE9 byte-verified; 9042-variant; HYPOTHESIS.
; ORIGIN 0x9281
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #7
	mvmd   al,0x3224
	stm    #188,brc
	call   0x9042
	stm    #12836,ar7
	stm    #3,brc
	call   0x9042
	stm    #188,brc
	call   0x9315
	sftl   a,3
	sth    a,*ar3-
	stl    a,*ar3
	rpt    #11
	mvdk   *ar3+,0x2f80
	ret
