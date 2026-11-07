; ROM6 0x7F55 SUB32_7F55 -- 31w, symbols.yaml data_word.
; Evidence: Entry F074 059E 6DEA 0007; RET @7F74 len 32; 12 callers (8x 7EBE-7F12 + 838E/83A2/83EA/8401); inner 0x059E only; dual E900/6DB3 lanes; sibling of 0x7FC6; HYPOTHESIS. Head Bound 7F5
; ORIGIN 0x7F55
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	mar    *+ar2(0x7)
	mvmm   ar2,ar1
	stm    #6,ar5
	ld     #0,b
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	stl    b,*ar2-
	ld     #0,b
	stm    #7,brc
	rptb   0x7f6f
	mvdk   *ar6+,0x13
	mar    *ar3+0
	ld     *ar3,ts,a
	ror    a
	rol    b
	sfta   b,1
	banzd  0x7f64,*ar5-
	sftl   b,-1
	stl    b,*ar2-
