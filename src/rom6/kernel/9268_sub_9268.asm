; ROM6 0x9268 SUB_9268 -- 25w, symbols.yaml data_word.
; Evidence: Bound 9268-9280 (25w; exit RET FC00@9280); entry F074 0594; caller F274@0x4BB8 byte-verified; 9042-variant; HYPOTHESIS.
; ORIGIN 0x9268
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #7
	mvmd   al,0x3224
	stm    #38,brc
	call   0x9042
	stm    #12836,ar7
	stm    #3,brc
	call   0x9042
	stm    #38,brc
	call   0x9315
	sftl   a,9
	stl    a,*ar3
	ret
