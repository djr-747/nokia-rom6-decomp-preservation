; ROM6 0x7F75 SUB_7F75 -- 32w, symbols.yaml data_word.
; Evidence: Entry F074 7FB5 7715 0006 E900 7196 (call 7FB5); callers 2x F274 calld @83B7/@83D1 objdump-verified (F273 bd @7F1E/7F24/7F2A/7F30 NOT counted); interior uncond b 7F54 @7F93; shrunk
; ORIGIN 0x7F75
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x7fb5
	stm    #6,ar5
	ld     #0,b
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	or     *ar2,b
	stl    b,*ar2-
	ld     #0,b
	stm    #7,brc
	rptb   0x7f8d
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	sfta   b,1
	sftl   b,-1
	banzd  0x7f82,*ar5-
	or     *ar2,b
	stl    b,*ar2-
	b      0x7f54
