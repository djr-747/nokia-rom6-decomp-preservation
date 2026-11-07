; ROM6 0xBE22 BUTTERFLY_BE22 -- 255w, symbols.yaml data_word.
; Evidence: Entry F074 06DE; add/sub butterfly on 0x2F00-0x2F08 tables + norm/mpy; first-RET @0xBF20 (len 255); callers BF23 BF7B-calld; HYPOTHESIS butterfly kernel.
; ORIGIN 0xBE22
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6de
	st     #23170,0x56
	stm    #350,st1
	stm    #128,ar0
	stm    #12032,ar2
	rpt    #255
	mvkd   0x3000,*ar2+0B
	stm    #12032,ar2
	stm    #12034,ar3
	stm    #12036,ar4
	stm    #7,ar0
	stm    #0,bk
	stm    #31,brc
	rptbd  0xbe5a
	stm    #12038,ar5
	sub    *ar2,*ar3,b
	add    *ar2,*ar3,a
	sth    b,asm,*ar3
	add    *ar4,*ar5,b
	add    b,a
	sth    a,asm,*ar2+
	sub    b,1,a
	sub    *ar4,*ar5,b
	st     a,*ar4+ || ld     *ar3,a
	sth    b,asm,*ar5+
	sub    *ar4,*ar5-,b
	add    b,asm,a
	sth    a,*ar3+
	sub    b,-1,a
	ld     *ar5,16,b
	sth    a,*ar5+
	add    *ar4,*ar5,a
	sth    a,asm,*ar4
	sub    *ar2,*ar3,a
	add    b,2,a
	sth    a,asm,*ar5+0
	sub    b,3,a
	add    *ar2,*ar3,b
	st     a,*ar3+0% || ld     *ar4,a
	add    a,2,b
	sth    b,asm,*ar2+0
	sub    a,3,b
	sth    b,asm,*ar4+0
	stm    #12032,ar2
	stm    #12040,ar3
	ld     #-1,asm
	ld     0x56,t
	stm    #15,brc
	rptbd  0xbe8a
	stm    #9,ar0
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	sth    b,asm,*ar3+
	mpy    *ar3+,a
	mac    *ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	sth    b,asm,*ar2+
	ld     *ar2+,16,a
	sub    *ar2-,*ar3+,b
	add    *ar3-,16,a
	sth    a,asm,*ar2+
	sth    b,asm,*ar2+
	add    *ar3,16,b
	add    *ar3+,16,b
	sub    *ar3,16,a
	sub    *ar3-,16,a
	sth    a,asm,*ar3+
	st     b,*ar3+ || ld     *ar2,a
	mpy    *ar3+,a
	mas    *ar3-,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	st     b,*ar2+ || mac    *ar3,a
	mac    *ar3,a
	add    *ar2,16,a,b
	st     b,*ar3+0% || sub    *ar2,b
	sth    b,asm,*ar2+0%
	stm    #12032,ar2
	stm    #12048,ar3
	stm    #16,ar0
	stm    #7,ar1
	stm    #-17185,ar6
	stm    #-17189,ar7
	mvmm   ar6,ar4
	mvmm   ar7,ar5
	stm    #6,brc
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	rptbd  0xbead
	st     b,*ar3+ || ld     *ar4,t
	mpy    *ar3+,a
	mac    *ar5+,*ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,*ar4+,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	ld     *ar4,t
	st     b,*ar2+ || mpy    *ar3+,a
	mar    *ar3-
	banzd  0xbe97,*ar1-
	mar    *ar2+0
	mar    *ar3+0
	stm    #12032,ar2
	stm    #12064,ar3
	stm    #32,ar0
	stm    #3,ar1
	stm    #-17028,ar6
	stm    #-17036,ar7
	mvmm   ar6,ar4
	mvmm   ar7,ar5
	stm    #14,brc
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	rptbd  0xbed5
	st     b,*ar3+ || ld     *ar4,t
	mpy    *ar3+,a
	mac    *ar5+,*ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,*ar4+,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	ld     *ar4,t
	st     b,*ar2+ || mpy    *ar3+,a
	mar    *ar3-
	banzd  0xbebf,*ar1-
	mar    *ar2+0
	mar    *ar3+0
	stm    #12032,ar2
	stm    #12096,ar3
	stm    #64,ar0
	stm    #1,ar1
	stm    #-17067,ar6
	stm    #-17083,ar7
	mvmm   ar6,ar4
	mvmm   ar7,ar5
	stm    #30,brc
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	rptbd  0xbefd
	st     b,*ar3+ || ld     *ar4,t
	mpy    *ar3+,a
	mac    *ar5+,*ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,*ar4+,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	ld     *ar4,t
	st     b,*ar2+ || mpy    *ar3+,a
	mar    *ar3-
	banzd  0xbee7,*ar1-
	mar    *ar2+0
	mar    *ar3+0
	stm    #12032,ar2
	stm    #12160,ar3
	stm    #-17146,ar4
	stm    #-17178,ar5
	stm    #62,brc
	ld     *ar2,16,a
	sub    *ar3,16,a,b
	st     b,*ar3 || add    *ar3+,b
	st     b,*ar2+ || ld     *ar3,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	rptbd  0xbf1f
	st     b,*ar3+ || ld     *ar4,t
	mpy    *ar3+,a
	mac    *ar5+,*ar3-,a
	add    *ar2,16,a,b
	st     b,*ar2 || sub    *ar2+,b
	st     b,*ar3 || mpy    *ar3+,a
	mas    *ar3,*ar4+,a
	add    *ar2,16,a,b
	st     b,*ar3+ || sub    *ar2,b
	ld     *ar4,t
	st     b,*ar2+ || mpy    *ar3+,a
	ret
