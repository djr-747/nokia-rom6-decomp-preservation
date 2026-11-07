; ROM6 0xBFB7 FRAG_BFB7 -- 29w, symbols.yaml data_word.
; Evidence: Bound BFB7-BFD3 (29w; exit RETD FE00@BFD1 + delays BFD2-BFD3 (sth/strcd 2w), byte-verified; exit scan clean); entry bcd FA44@BFB0->BFB7 byte-verified (cond aneq, exterior from NORM
; ORIGIN 0xBFB7
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #-17222,ar1
	ld     0x68,t
	ld     *ar1-,16,a
	ld     *ar1-,16,b
	rpt    #2
	poly   *ar1-
	macar  t,b,a
	mpya   a
	add    0x68,16,a
	ld     a,-1,a
	add    *ar1,16,a
	ld     *ar2,15,b
	adds   0x42,b
	sth    b,*ar2-
	and    0x42,b
	add    0x41,12,a
	bc     0xbfd4,beq
	sat    a
	sth    a,0x68
	squr   0x68,b
	sub    *ar2,16,b
	mas    0x41,b
	sub    0x41,16,a
	retd
	sth    a,*ar2
	strcd  *ar2,bleq
