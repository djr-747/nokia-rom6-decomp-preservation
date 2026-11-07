; ROM6 0x44BD FRAG_44BD -- 26w, symbols.yaml data_word.
; Evidence: Bound 44BD-44D6 (26w; exit RET FC00@44D6 byte-verified); post-RET head (FC00@44BC = FRAG_44B2 exit); interior out-calls call@44BD->0594 + call@44BF->2E2F + calld@44D2->2C88; chain 
; ORIGIN 0x44BD
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	call   0x2e2f
	stm    #12032,ar3
	ld     #10,8,a
	or     #9,a
	stl    a,*ar3+
	stm    #96,ar2
	st     #256,*ar2
	mvdp   *ar2,0xff87
	stm    #116,ar4
	mvpd   0xff87,*ar3-
	calld  0x2c88
	stm    #4,ar5
	ret
