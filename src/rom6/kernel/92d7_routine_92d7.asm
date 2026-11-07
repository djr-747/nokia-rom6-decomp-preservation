; ROM6 0x92D7 ROUTINE_92D7 -- 29w, symbols.yaml data_word.
; Evidence: Bound 92D7-92F3 (29w; exit RET FC00@92F3 byte-verified, exit scan clean; head F074 0594 call idiom); entries calld F274@494->92D7 byte-verified (from 8210-setB block08) + post-RET 
; ORIGIN 0x92D7
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #7
	mvmd   al,0x3224
	stm    #243,brc
	call   0x9042
	stm    #12836,ar7
	stm    #3,brc
	call   0x9042
	stm    #243,brc
	call   0x9315
	sftl   a,12
	sth    a,*ar3-
	stl    a,*ar3
	rpt    #15
	mvdk   *ar3+,0x2f80
	ret
