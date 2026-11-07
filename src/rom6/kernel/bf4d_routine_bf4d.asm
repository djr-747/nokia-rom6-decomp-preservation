; ROM6 0xBF4D ROUTINE_BF4D -- 63w, symbols.yaml data_word.
; Evidence: Bound BF4D-BF8B (63w; exit RET FC00@BF8B byte-verified, exit scan clean); entries call F074@BDFD-> BF4D byte-verified + post-RET head (FE00@BF4C retd of ROUTINE_BF21); interior cal
; ORIGIN 0xBF4D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6de
	stm    #12032,ar2
	rpt    #255
	mvkd   0x3000,*ar2+
	stm    #62,brc
	stm    #12032,ar2
	stm    #12287,ar5
	stm    #12288,ar3
	mvdd   *ar2+,*ar3+
	rptbd  0xbf64
	stm    #12415,ar4
	sub    *ar2,*ar5,a
	add    *ar2+,*ar5-,b
	sth    a,*ar3+
	sth    b,*ar4-
	mvdd   *ar2,*ar3
	stm    #62,brc
	stm    #12160,ar2
	stm    #12416,ar3
	stm    #12543,ar4
	stm    #12159,ar5
	ld     *ar2+,16,a
	rptbd  0xbf79
	neg    a,b
	sth    b,*ar3+
	add    *ar5,*ar2,a
	sub    *ar5-,*ar2+,b
	neg    a
	sth    a,*ar3+
	sth    b,*ar4-
	ld     *ar2,16,a
	calld  0xbe22
	neg    a
	sth    a,*ar3
	ld     #0,asm
	stm    #0,bk
	ld     0x42,t
	stm    #12033,ar2
	stm    #2,ar0
	mvmm   ar2,ar3
	mpy    *ar2+0,a
	rpt    #127
	st     a,*ar3+0% || mpy    *ar2+0%,a
	ret
