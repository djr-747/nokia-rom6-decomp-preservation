; ROM6 0x92BB ROUTINE_92BB -- 28w, symbols.yaml data_word.
; Evidence: Bound 92BB-92D6 (28w; exit RET FC00@92D6 byte-verified; interior clean — second RET@92F3 belongs to sibling ROUTINE_92D7; exit scan otherwise clean; head F074 0594 call idiom); ent
; ORIGIN 0x92BB
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #11
	mvmd   al,0x3224
	stm    #75,brc
	call   0x9071
	stm    #12836,ar7
	stm    #3,brc
	call   0x9071
	stm    #75,brc
	call   0x9315
	sftl   a,4
	stl    a,*ar3
	rpt    #4
	mvdk   *ar3+,0x2f80
	ret
