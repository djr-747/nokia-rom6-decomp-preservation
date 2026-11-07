; ROM6 0xC5EA MINMAX_TRIO_C5C3 -- 15w, symbols.yaml data_word.
; Evidence: Entry F074 0692; bounds C5C3-C5D1 + C5D2-C5E9 + C5EA-C5F8 (callerless MASR twin); callers C61F calld->C5C3, C636/C638/C642->C5D2; C5F8 abuts C5F9 head; HYPOTHESIS.
; Pool: MASR dual (oracle-unbound; max/min grounded but span fails on masr); stays .asm, bytes verified.
; Pool: MASR dual (oracle-unbound; max/min grounded but span fails on masr); stays .asm, bytes verified.
; ORIGIN 0xC5EA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1,brc
	rptb   0xc5f7
	bitf   *ar3,#-32768
	ld     *ar5,16,b
	masr   *ar3+,*ar5,b
	ld     *ar1+,16,a
	xc     1,ntc
	max    a
	xc     1,tc
	min    a
	sth    a,*ar5+
	ret
