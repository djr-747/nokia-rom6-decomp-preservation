; ROM6 0xDC43 SUB_DC43 -- 52w, symbols.yaml data_word.
; Evidence: Entry 7711 0C48 F071 0003; first exit ret FC00 @DC76; caller F274 @DFE2 verified; HYPOTHESIS.
; ORIGIN 0xDC43
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #3144,ar1
	rptz   a,#3
	stl    a,*ar1+
	stm    #3159,ar1
	st     #4096,*ar1+
	rpt    #9
	stl    a,*ar1+
	stm    #3170,ar2
	rpt    #9
	mvkd   0xfb9c,*ar2+
	stm    #3180,ar2
	rpt    #9
	mvkd   0xfb9c,*ar2+
	stm    #3190,ar2
	rpt    #29
	stl    a,*ar2+
	stm    #3220,ar2
	rpt    #9
	stl    a,*ar2+
	stm    #3394,ar2
	rpt    #81
	stl    a,*ar2+
	stm    #3234,ar2
	rpt    #159
	stl    a,*ar2+
	stm    #3636,ar2
	rpt    #142
	stl    a,*ar2+
	ld     #-2381,a
	stm    #3230,ar2
	rpt    #3
	stl    a,*ar2+
	call   0xe5ba
	call   0xd9e1
	ret
