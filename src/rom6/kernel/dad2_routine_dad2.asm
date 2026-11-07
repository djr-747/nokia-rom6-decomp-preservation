; ROM6 0xDAD2 ROUTINE_DAD2 -- 43w, symbols.yaml data_word.
; Evidence: Bound DAD2-DAFC (43w; exit RETD FE00@DAFA + delays DAFB-DAFC (rpt/sth 2w), byte-verified; exit scan clean); entry ccd FB45@D2A7->DAD2 byte-verified (cond aeq call — CCD confers ent
; ORIGIN 0xDAD2
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #16,a
	and    0x5a,a
	bcd    0xdadd,aeq
	stm    #2662,ar3
	rpt    #4
	mvkd   0xed6,*ar3+
	mvkd   0xf0e,*ar3
	ld     #32,a
	and    0x5a,a
	bcd    0xdaef,aeq
	stm    #2662,ar3
	rpt    #4
	mvdk   *ar3+,0xed6
	ld     *ar3,a
	stl    a,*(0xee7)
	stl    a,*(0xef4)
	stl    a,*(0xf01)
	stl    a,*(0xf0e)
	stm    #3803,ar3
	rpt    #11
	sth    a,*ar3+
	mar    *ar3+
	rpt    #11
	sth    a,*ar3+
	mar    *ar3+
	rpt    #11
	sth    a,*ar3+
	mar    *ar3+
	retd
	rpt    #11
	sth    a,*ar3+
