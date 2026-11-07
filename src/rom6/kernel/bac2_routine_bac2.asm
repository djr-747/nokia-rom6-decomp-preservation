; ROM6 0xBAC2 ROUTINE_BAC2 -- 25w, symbols.yaml data_word.
; Evidence: Bound BAC2-BADA (25w; exit RETD FE00@BAD8 + delays BAD9-BADA (7313 054A) included per wave-1 convention; exit scan otherwise clean; BADB+ stays dark — exterior call target, unenter
; ORIGIN 0xBAC2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6a6
	bitf   *(0x577),#8
	bc     0xbacd,ntc
	mvmm   ar2,ar3
	rptz   a,#159
	stl    a,*ar3+
	stm    #632,bk
	mvdm   0x54a,ar3
	stm    #159,brc
	rptbd  0xbad7
	stm    #1,ar0
	mvdd   *ar2+,*ar3+0%
	retd
	mvmd   ar3,0x54a
