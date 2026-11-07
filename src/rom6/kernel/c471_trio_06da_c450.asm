; ROM6 0xC471 TRIO_06DA_C450 -- 27w, symbols.yaml data_word.
; Evidence: Entry F074 06DA; bounds C450-C45F + C460-C470 + C471-C48B (call C53D@C47A); callers BE04/BE0D calld->C450, BDF6/BDFB->C460, BE13/BE1B calld->C471; BRC 87/127 + RPTBD fills; HYPOTHE
; ORIGIN 0xC471
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6da
	mvmm   ar4,ar6
	mvmm   ar2,ar7
	ld     *(0x2aea),a
	bc     0xc47e,aleq
	mvmm   ar2,ar1
	call   0xc53d
	mvmm   ar6,ar4
	mvmm   ar7,ar2
	stm    #7,brc
	rptbd  0xc485
	stm    #10412,ar3
	add    *ar2+,*ar3+,a
	sth    a,*ar4+
	rpt    #71
	mvdd   *ar2+,*ar4+
	rpt    #7
	mvdk   *ar2+,0x28ac
	ret
