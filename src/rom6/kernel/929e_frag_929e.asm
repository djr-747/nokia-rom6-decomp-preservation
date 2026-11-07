; ROM6 0x929E FRAG_929E -- 29w, symbols.yaml data_word.
; Evidence: Bound 929E-92BA (29w; exit RET FC00@92BA byte-verified, exit scan clean); post-RET head only (FC00@929D, zero exterior refs — thin entry); head F074 0594; interior out-calls ->9217
; ORIGIN 0x929E
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x9217
	ld     #127,a
	rpt    #11
	mvmd   al,0x3224
	stm    #151,brc
	call   0x9071
	stm    #12836,ar7
	stm    #3,brc
	call   0x9071
	stm    #151,brc
	call   0x9315
	sftl   a,8
	sth    a,*ar3-
	stl    a,*ar3
	rpt    #9
	mvdk   *ar3+,0x2f80
	ret
