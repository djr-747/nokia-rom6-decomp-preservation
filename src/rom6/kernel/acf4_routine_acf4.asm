; ROM6 0xACF4 ROUTINE_ACF4 -- 25w, symbols.yaml data_word.
; Evidence: Bound ACF4-AD0C (25w; exit RET FC00@AD0C byte-verified; interior joins B@ACFB->AD0A + B@AD04->AD0A in-span; exit scan otherwise clean); entry call F074@43B->ACF4 byte-verified (fro
; ORIGIN 0xACF4
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x3e7e),#4
	bc     0xacfd,ntc
	sth    a,*ar2+
	stl    a,*ar2+
	b      0xad0a
	bitf   *(0x3e7e),#2
	bc     0xad06,tc
	sth    a,*ar2+
	sth    a,*ar2+
	b      0xad0a
	stm    #16001,ar5
	mvdd   *ar5+,*ar2+
	mvdd   *ar5+,*ar2+
	call   0xae22
	ret
