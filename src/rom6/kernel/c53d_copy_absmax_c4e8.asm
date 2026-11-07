; ROM6 0xC53D COPY_ABSMAX_C4E8 -- 25w, symbols.yaml data_word.
; Evidence: Entry MVMD 0x3148/49; bounds C4E8-C53C + C53D-C555 (called from C47A); callers BD15/BD20 calld; RPTBD TMPYR + BRC 87 ABS/MAX + RPT #87 ST||ADD; HYPOTHESIS.
; ORIGIN 0xC53D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6dc
	mvmm   ar1,ar2
	stm    #7,brc
	rptbd  0xc548
	stm    #-17221,ar3
	ld     *ar2,t
	mpyr   *ar3+,a
	sth    a,*ar2+
	mvmm   ar1,ar4
	stm    #7,brc
	stm    #-17214,ar2
	rptbd  0xc554
	mar    *+ar4(0x50)
	ld     *ar2-,t
	mpyr   *ar4,a
	sth    a,*ar4+
	ret
