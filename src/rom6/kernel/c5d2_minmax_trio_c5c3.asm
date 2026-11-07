; ROM6 0xC5D2 MINMAX_TRIO_C5C3 -- 24w, symbols.yaml data_word.
; Evidence: Entry F074 0692; bounds C5C3-C5D1 + C5D2-C5E9 + C5EA-C5F8 (callerless MASR twin); callers C61F calld->C5C3, C636/C638/C642->C5D2; C5F8 abuts C5F9 head; HYPOTHESIS.
; ORIGIN 0xC5D2
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x692
	sub    *ar4,*ar2+,a
	bc     0xc5ea,alt
	sub    *ar4,*ar2-,a
	rc     alt
	mar    *+ar1(0x2)
	stm    #1,brc
	rptb   0xc5e8
	bitf   *ar3,#-32768
	ld     *ar5,16,b
	macr   *ar3+,*ar5,b
	ld     *ar1+,16,a
	xc     1,tc
	max    a
	xc     1,ntc
	min    a
	sth    a,*ar5+
	ret
