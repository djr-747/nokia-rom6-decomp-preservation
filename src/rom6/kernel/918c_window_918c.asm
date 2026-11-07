; ROM6 0x918C WINDOW_918C -- 50w, symbols.yaml data_word.
; Evidence: Entry F074 0610 7713 30BE; BOUND CONFIRMED entry-linear (interior 0x91AE FC00 is operand trap, not exit); rptb copy + rpt zero-fill; first-RET FC00 @0x91BD len 53 (extended through
; ORIGIN 0x918C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x610
	stm    #12478,ar3
	stm    #12496,ar4
	stm    #12511,ar5
	stm    #7,brc
	rptb   0x919d
	ld     *+ar3(0x2),-6,a
	stl    a,*ar4+
	neg    a
	stl    a,*ar5-
	mar    *+ar3(0x2)
	rpt    #15
	mvdk   *ar3+,0x30c0
	stm    #9,ar0
	stm    #12824,ar3
	stm    #12800,ar5
	stm    #12816,ar4
	stm    #32,bk
	ld     #-512,a
	rpt    #31
	stl    a,*ar5+
	stm    #12800,ar5
	ld     #0,a
	stm    #12832,ar1
	stm    #12834,ar6
	stl    a,*ar1+
	stl    a,*ar1-
	stl    a,*ar5
	stm    #12480,ar2
	ret
