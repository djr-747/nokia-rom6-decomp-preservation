; ROM6 0x91BE WINDOW_918C-driver-E2 -- (overlap-split wave-12).
; Evidence: Entry call 0x594 (dark) @91BE... word0 ret FC00 @91BD owned by 918c_window_918c (918C exit). Former head word trimmed; span now 91BE-91F1. C intent in 91bd_window_918c.c (EXPECT keeps word0 verified-not-modeled, 644a precedent). Recombine-clean.
; ORIGIN 0x91BE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	ld     #100,a
	rpt    #3
	mvmd   al,0x3032
	stm    #128,ar6
	stm    #12196,ar7
	stm    #42,brc
	rptb   0x91ce
	ld     *ar7+,-6,a
	stl    a,*ar6+
	stm    #12299,ar7
	stm    #42,brc
	rptb   0x91d7
	ld     *ar7+,-6,a
	stl    a,*ar6+
	call   0x918c
	stm    #128,ar7
	stm    #85,brc
	call   0x9004
	stm    #132,ar7
	stm    #128,ar3
	stm    #38,brc
	rptb   0x91e9
	ld     *ar7+,b
	stl    b,*ar3+
	mar    *+ar7(0x4)
	stm    #38,brc
	rptb   0x91f1
	ld     *ar7+,b
	stl    b,*ar3+

