; ROM6 0x7F95 SUB32_7F95 -- 30w, symbols.yaml data_word.
; Evidence: Post-unconditional-b head (F073 b @7F93, backscan 7F7D-7F94 exit-free); entry F074 059E 7715 0006; bound shrunk to interior F073 b @7FB3->7F54 incl operand 7FB4 len 32, tail-merges
; ORIGIN 0x7F95
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #6,ar5
	ld     #0,b
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	sfta   b,1
	or     *ar1,b
	stl    b,*ar1-
	ld     #0,b
	stm    #7,brc
	rptb   0x7fae
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	sfta   b,1
	banzd  0x7fa3,*ar5-
	or     *ar1,b
	stl    b,*ar1-
